#include "mozo/php/module.hpp"
#include "mozo/php/function.hpp"

using namespace mozo;

class m003_module
    : public php::module,
      public php::function_container<m003_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m003_module* mod)
            :php::module::handler(mod) {}

        php::value_ptr concat_and_uppercase(
                std::string a, std::string b) {
            php::function strtoupper("strtoupper");
            return strtoupper(a + b);
        }
    };
public:
    m003_module(zend_module_entry* entry)
        : php::module(entry) {
        entry->functions =
             defun("concat_and_uppercase", &handler::concat_and_uppercase);
    }
};

#define MOZO_PHP_MODULE_NAME m003
#define MOZO_PHP_MODULE_CAPITALIZED_NAME M003
#define MOZO_PHP_MODULE_VERSION "0.1"
#define MOZO_PHP_MODULE_CLASS_NAME m003_module

#include "mozo/php/module_def.hpp"
