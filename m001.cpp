#include "boost/php/module.hpp"

using namespace boost;

class m001_module
    : public php::module {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m001_module* mod)
            :php::module::handler(mod) {}
    };
public:
    m001_module(zend_module_entry* entry)
        : php::module(entry) {
    }
};

#define BOOST_PHP_MODULE_NAME m001
#define BOOST_PHP_MODULE_CAPITALIZED_NAME M001
#define BOOST_PHP_MODULE_VERSION "0.1"
#define BOOST_PHP_MODULE_CLASS_NAME m001_module

#include "boost/php/module_def.hpp"
