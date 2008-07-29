//
// Copyright 2008 (C) Moriyoshi Koizumi. All rights reserved.
//
// This software is distributed under the Boost Software License, Version 1.0.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef MOZO_PHP_DETAIL_FUNCTION_CONTAINER_HPP
#define MOZO_PHP_DETAIL_FUNCTION_CONTAINER_HPP

#include <vector>
#include <cstring>
#include <map>
#include <boost/shared_ptr.hpp>

#include <zend.h>

#include <mozo/php/detail/arg_info_factory.hpp>
#include <mozo/php/detail/native_fun_proxy.hpp>

namespace mozo { namespace php {

struct function_entry: public ::zend_function_entry {
    function_entry() {
        fname = 0;
        handler = 0;
        arg_info = 0;
        num_args = 0;
        flags = 0;
    }

    function_entry(
            const char* _name,
            void (*_handler)(INTERNAL_FUNCTION_PARAMETERS),
            ::zend_arg_info* _arg_info_list,
            ::zend_uint _num_args,
            ::zend_uint _flags) {
        fname = const_cast<char*>(_name);
        handler = _handler;
        arg_info = _arg_info_list;
        num_args = _num_args;
        flags = _flags;
    }

    bool is_sentinel() const {
        return !fname;
    }
};

template<typename T_>
class function_container {
public:
    typedef ::std::map< ::zend_arg_info*, detail::native_fun_proxy_base*> handler_map_type;
    typedef ::std::vector<function_entry> entry_array_type;

public:
    function_container() {
    }

    ~function_container() {
        for (entry_array_type::iterator i(functions_.begin());
                i != functions_.end(); ++i) {
            delete[] i->fname;
        }
        if (handlers_) {
            for (handler_map_type::iterator i(handlers_->begin());
                    i != handlers_->end(); ++i) {
                delete i->first;
                delete i->second;
            }
            delete handlers_;
            handlers_ = 0;
        }
    }

    template<typename Tsig_>
    function_entry const& define_function(
            ::std::string const& name, Tsig_ const& sig) {
        if (!handlers_) {
            handlers_ = new handler_map_type();
            handlers_->insert(typename handler_map_type::value_type(0, 0));
        }
        ::zend_arg_info* info = detail::create_arg_info(sig);

        ::std::pair<handler_map_type::iterator, bool> r(
                handlers_->insert(typename handler_map_type::value_type(
                    info,
                    detail::create_native_fun_proxy(sig)))
                );
        if (!functions_.empty() && functions_.back().is_sentinel())
            functions_.pop_back();
        functions_.push_back(function_entry(
                dup_str(name),
                &function_container::__fcall_handler,
                info, sig.arity(), sig.is_static() ? ZEND_ACC_STATIC: 0)); 
        return functions_.back();
    }

    template<typename Tfunc_>
    function_entry const& define_function(
            ::std::string const& name, Tfunc_ f, bool) {
        return static_cast<T_*>(this)->define_function(name, detail::get_signature(f));
    }

    template<typename Tfunc_>
    T_& defun(::std::string const& name, Tfunc_ f) {
        define_function(name, f, true);
        return *static_cast<T_*>(this);
    }

    operator ::zend_function_entry*() {
        append_sentinel();
        return static_cast<function_entry*>(&functions_[0]);
    };

    operator ::zend_function_entry const*() const {
        append_sentinel();
        return static_cast<function_entry*>(&functions_[0]);
    };

    typename entry_array_type::size_type size() const {
        return !functions_.empty() && functions_.back().is_sentinel() ?
                functions_.size() - 1: functions_.size();
    }
protected:
    void append_sentinel() {
        if (functions_.empty() ||
                !functions_.back().is_sentinel()) {
            functions_.push_back(function_entry());
        }
    }

private:
    static char* dup_str(const ::std::string& val) {
        char* retval = new char[val.size() + 1];
        ::std::memcpy(retval, val.data(), val.size());
        retval[val.size()] = 0;
        return retval;
    }

    static void __fcall_handler(INTERNAL_FUNCTION_PARAMETERS) {
        (*(*handlers_)[
            EG(current_execute_data)->function_state.function->common.arg_info - 1])(
                INTERNAL_FUNCTION_PARAM_PASSTHRU);
    }

protected:
    static handler_map_type* handlers_;
    mutable entry_array_type functions_;
};

template<typename T_>
typename function_container<T_>::handler_map_type*
function_container<T_>::handlers_;

} } // namespace mozo::php

#endif /* MOZO_PHP_DETAIL_FUNCTION_CONTAINER_HPP */
