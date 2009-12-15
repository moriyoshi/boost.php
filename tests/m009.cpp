#include "boost/php/module.hpp"
#include "boost/php/function.hpp"
#include "boost/php/klass.hpp"
#include <boost/mpl/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <Zend/zend_interfaces.h>
#include <iostream>

using namespace boost;

class RangeIterator {
public:
    RangeIterator(int start, int end): cnt_(start), till_(end) {}

    int current() const {
        return cnt_;
    }

    int key() const {
        return cnt_;
    }

    void rewind() {
        cnt_ = 0;
    }

    bool valid() const {
        return cnt_ < till_;
    }

    void next() {
        ++cnt_;
    }

private:
    int cnt_;
    const int till_;
};

class m009_module
    : public php::module,
      public php::function_container<m009_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m009_module* mod)
            : php::module::handler(mod) {}

        void __initialize(TSRMLS_D) {
            php::def_class<RangeIterator>("RangeIterator", boost::mpl::vector2<int, int>() TSRMLS_CC)
                .implements(::zend_ce_iterator)
                .defun("rewind", &RangeIterator::rewind)
                .defun("key", &RangeIterator::key)
                .defun("current", &RangeIterator::current)
                .defun("next", &RangeIterator::next)
                .defun("valid", &RangeIterator::valid)
                .fixup();
        }
    };
public:
    m009_module(zend_module_entry* entry)
            : php::module(entry) {
    }
};

#define BOOST_PHP_MODULE_NAME m009
#define BOOST_PHP_MODULE_CAPITALIZED_NAME M008
#define BOOST_PHP_MODULE_VERSION "0.1"
#define BOOST_PHP_MODULE_CLASS_NAME m009_module

#include "boost/php/module_def.hpp"
