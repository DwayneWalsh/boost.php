#include "mozo/php/module.hpp"
#include "mozo/php/function.hpp"
#include "mozo/php/klass.hpp"
#include <iostream>

using namespace mozo;

class test {
public:
    test(): acc_(2) {
    }

    int accumulate(int a) {
        acc_ += a;
        return acc_;
    }

    static void foo(test const& t) {
        std::cout << t.acc_ << std::endl;
    }

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
            php::def_class<test>("test" TSRMLS_CC)
                .defun("accumulate", &test::accumulate)
                .defun("foo", &test::foo)
                .fixup();
        }
    };
public:
    m008_module(zend_module_entry* entry)
            : php::module(entry) {
    }
};

#define MOZO_PHP_MODULE_NAME m008
#define MOZO_PHP_MODULE_CAPITALIZED_NAME M008
#define MOZO_PHP_MODULE_VERSION "0.1"
#define MOZO_PHP_MODULE_CLASS_NAME m008_module

#include "mozo/php/module_def.hpp"