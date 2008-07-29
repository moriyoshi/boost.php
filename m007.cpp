#include "boost/php/module.hpp"
#include "boost/php/function.hpp"

using namespace boost;

class m007_module
    : public php::module,
      public php::function_container<m007_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m007_module* mod)
            :php::module::handler(mod), acc_(0) {}

        int accumulate(int a) {
            acc_ += a;
            return acc_;
        }

    protected:
        int acc_;
    };
public:
    m007_module(zend_module_entry* entry)
        : php::module(entry) {
        entry->functions =
             defun("accumulate", &handler::accumulate);
    }
};

#define MOZO_PHP_MODULE_NAME m007
#define MOZO_PHP_MODULE_CAPITALIZED_NAME M007
#define MOZO_PHP_MODULE_VERSION "0.1"
#define MOZO_PHP_MODULE_CLASS_NAME m007_module

#include "boost/php/module_def.hpp"
