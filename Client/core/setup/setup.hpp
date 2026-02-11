#ifndef SETUP_HPP
#define SETUP_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

namespace lso {

    class Setup {

        public:

            static std::string getPlayerName();

            static void connectToServer();

        protected:

            //...

        private:

            Setup();

    };

}

#endif
