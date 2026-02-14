#ifndef SPINNER_HPP
#define SPINNER_HPP

#include <iostream>
#include <string>
#include <functional>
#include <future>

namespace lso {

    class Spinner {
        private:
        
            static inline constexpr char symbols[] = {'|', '/', '-', '\\'};
            static inline constexpr int length = sizeof(symbols);
            
            Spinner();
        
        protected:
        
            //...
        
        public:
        
            template <typename Data>
            static Data showLoadingTextOnFunction(const std::string & text, std::function<Data()> function) {

                std::future<Data> future = std::async(std::launch::async, function);

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

            Spinner &operator = (const Spinner &) = delete;

            Spinner &operator = (Spinner &&) noexcept = delete;

            bool operator == (const Spinner &) const noexcept = delete;
            bool operator != (const Spinner &) const noexcept = delete;

    };

}

#endif
