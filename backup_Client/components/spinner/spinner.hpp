#ifndef SPINNER_HPP
#define SPINNER_HPP

#include <iostream>
#include <string>
#include <functional>
#include <future>

namespace lso {

    class Spinner {
        private:
        
            static inline const char symbols[] = {'|', '/', '-', '\\'};
            static inline const int length = sizeof(symbols);
            
        protected:
            
            //...
            
        public:
            
            template <typename Data, typename Function, typename... Args>
            static Data showLoadingTextOnFunction(const std::string & text, Function && function, Args &&... args) {
                
                std::future<Data> future = std::async(std::launch::async, std::forward<Function>(function), std::forward<Args>(args)...);
                
                for (unsigned int i = 0; future.wait_for(std::chrono::milliseconds(500)) != std::future_status::ready; i++) {
                    std::cout << "\r"
                    << text
                    << " "
                    << symbols[i % length]
                    << std::flush;
                }
                
                std::cout << "\b"
                << "✔"
                << std::endl
                << std::flush;
                
                return future.get();
            }    
            
            public:
            
                Spinner() = delete;
                Spinner(const Spinner &) = delete;
                Spinner(Spinner &&) noexcept = delete;

                ~Spinner() = delete;

                Spinner &operator = (const Spinner &) = delete;
                Spinner &operator = (Spinner &&) noexcept = delete;

                bool operator == (const Spinner &) const noexcept = delete;
                bool operator != (const Spinner &) const noexcept = delete;

    };

}

#endif
