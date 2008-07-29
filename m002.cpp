#include "mozo/php/module.hpp"
#include "mozo/php/function.hpp"

using namespace mozo;

class m002_module
    : public php::module,
      public php::function_container<m002_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m002_module* mod)
            :php::module::handler(mod) {}

        int add(int a, int b) {
            return a + b;
        }

        int sub(int a, int b) {
            return a - b;
        }
    };
public:
    m002_module(zend_module_entry* entry)
        : php::module(entry) {
        entry->functions =
             defun("add", &handler::add).
             defun("sub", &handler::sub);
    }
};

#define MOZO_PHP_MODULE_NAME m002
#define MOZO_PHP_MODULE_CAPITALIZED_NAME M002
#define MOZO_PHP_MODULE_VERSION "0.1"
#define MOZO_PHP_MODULE_CLASS_NAME m002_module

#include "mozo/php/module_def.hpp"
