#ifndef SETUP_HPP
#define SETUP_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include "../../components/spinner/spinner.hpp"
#include "../../components/screen/screen.hpp"

#include "../network/tcp/TCPClient.hpp"

namespace lso {

    class Setup {
        
        private:
            
            static bool validPlayerName(const std::string name) noexcept;
        
        protected:
        
            //...
        
        public:
        
            static std::string getPlayerName() noexcept;
            
            static std::unique_ptr<TCPClient> connectToServer(const std::string name);
            
        public:
        
            Setup() = delete;
            Setup(const Setup &) = delete;
            Setup(Setup &&) noexcept = delete;

            ~Setup() = default;

            Setup &operator = (const Setup &) = delete;
            Setup &operator = (Setup &&) noexcept = delete;

            bool operator == (const Setup &) const noexcept = delete;
            bool operator != (const Setup &) const noexcept = delete;
        
    };

}

#endif
