#include "mozo/php/module.hpp"
#include "mozo/php/function.hpp"

using namespace mozo;

class m004_module
    : public php::module,
      public php::function_container<m004_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m004_module* mod)
            :php::module::handler(mod) {}

        ::std::string array_func(const php::array& a, int idx) {
            return ::std::string("The content of array element #")
                   + static_cast< ::std::string>(php::value(idx)) + " is "
                   + static_cast< ::std::string>(*a[idx]) + ".";
        }
    };

public:
    m004_module(zend_module_entry* entry)
        : php::module(entry) {
        entry->functions =
             defun("array_func", &handler::array_func);
    }
};

#define MOZO_PHP_MODULE_NAME m004
#define MOZO_PHP_MODULE_CAPITALIZED_NAME M004
#define MOZO_PHP_MODULE_VERSION "0.1"
#define MOZO_PHP_MODULE_CLASS_NAME m004_module

#include "mozo/php/module_def.hpp"
