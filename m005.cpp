#include <iostream>
#include <algorithm>
#include "boost/php/module.hpp"
#include "boost/php/function.hpp"

using namespace boost;

class m005_module
    : public php::module,
      public php::function_container<m005_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m005_module* mod)
            :php::module::handler(mod) {}

        struct print {
            void operator()(php::array::const_reference r) {
                std::cout << r.second << std::endl;
            }
        };

        void array_iter(const php::array& a) {
            for (php::array::const_iterator i(a.begin()), e(a.end());
                    i != e; ++i) {
                std::cout << (::std::string)(*i).first << std::endl;
            }
            std::for_each(a.begin(), a.end(), print());
        }
    };

public:
    m005_module(zend_module_entry* entry)
        : php::module(entry) {
        entry->functions =
             defun("array_iter", &handler::array_iter);
    }
};

#define BOOST_PHP_MODULE_NAME m005
#define BOOST_PHP_MODULE_CAPITALIZED_NAME M005
#define BOOST_PHP_MODULE_VERSION "0.1"
#define BOOST_PHP_MODULE_CLASS_NAME m005_module

#include "boost/php/module_def.hpp"
