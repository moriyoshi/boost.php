#include "boost/php/module.hpp"
#include "boost/php/function.hpp"
#include "boost/php/klass.hpp"
#include <boost/mpl/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace boost;

class test {
public:
    test(int initial): acc_(initial) {
    }

    int accumulate(int a) {
        acc_ += a;
        return acc_;
    }

    static void foo(test const& t) {
        std::cout << t.acc_ << std::endl;
    }

    static boost::shared_ptr<test> create(int initial) {
        return boost::shared_ptr<test>(new test(initial));
    }

/*
    static boost::shared_ptr<test> create(int initial) {
        return boost::shared_ptr<test>(new test(initial));
    }
*/
protected:
    int acc_;
};

class m008_module
    : public php::module,
      public php::function_container<m008_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m008_module* mod)
            : php::module::handler(mod) {}

        void __initialize(TSRMLS_D) {
            php::def_class<test>("test", boost::mpl::vector1<int>() TSRMLS_CC)
                .defun("accumulate", &test::accumulate)
                .defun("foo", &test::foo)
                .defun("create", &test::create)
                .fixup();
        }
    };
public:
    m008_module(zend_module_entry* entry)
            : php::module(entry) {
    }
};

#define BOOST_PHP_MODULE_NAME m008
#define BOOST_PHP_MODULE_CAPITALIZED_NAME M008
#define BOOST_PHP_MODULE_VERSION "0.1"
#define BOOST_PHP_MODULE_CLASS_NAME m008_module

#include "boost/php/module_def.hpp"
