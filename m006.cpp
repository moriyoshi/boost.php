#include "boost/php/module.hpp"
#include "boost/php/function.hpp"

using namespace boost;

class m006_module
    : public php::module,
      public php::function_container<m006_module> {
public:
    class handler
        : public php::module::handler {
    public:
        handler(m006_module* mod)
            :php::module::handler(mod) {}

        php::value_ptr
        my_file_get_contents(::std::string filename) {
            php::function fopen("fopen"),
                          fread("fread"),
                          filesize("filesize"),
                          fclose("fclose");
            php::value_ptr $fp, $retval;

            MOZO_PHP_BEGIN_CAPTURE_ERROR
                $fp = fopen(filename, "rb");
                if (*$fp == false) {
                    throw php::runtime_error(
                        std::string("Failure in system function: \"")
                        + MOZO_PHP_LAST_ERROR.message() + "\"",
                        MOZO_PHP_LAST_ERROR.filename().c_str(),
                        MOZO_PHP_LAST_ERROR.line_number());
                }
            MOZO_PHP_END_CAPTURE_ERROR

            try {
                MOZO_PHP_BEGIN_CAPTURE_ERROR
                    $retval = fread($fp, filesize(filename));
                    if (*$retval == false) {
                        throw php::runtime_error(
                            std::string("Failure in system function: \"")
                            + MOZO_PHP_LAST_ERROR.message() + "\"",
                            MOZO_PHP_LAST_ERROR.filename().c_str(),
                            MOZO_PHP_LAST_ERROR.line_number());
                    }
                MOZO_PHP_END_CAPTURE_ERROR
            } catch (const ::std::exception&) {
                fclose($fp);
                throw;
            }
            
            fclose($fp);

            return $retval;
        }
    };

public:
    m006_module(zend_module_entry* entry)
        : php::module(entry) {
        entry->functions =
             defun("my_file_get_contents", &handler::my_file_get_contents);
    }
};

#define MOZO_PHP_MODULE_NAME m006
#define MOZO_PHP_MODULE_CAPITALIZED_NAME M006
#define MOZO_PHP_MODULE_VERSION "0.1"
#define MOZO_PHP_MODULE_CLASS_NAME m006_module

#include "boost/php/module_def.hpp"
