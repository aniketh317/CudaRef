#include <thread>
#include <iostream>

int main()
{
    const auto processor_count = std::thread::hardware_concurrency();
    std::cout<<"Number of processors: "<<processor_count<<std::endl;
    return 0;
}