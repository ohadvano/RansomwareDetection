// 'Hello World!' program 
 
#include <iostream>
#include "ConfigurationProvider.cpp"

using namespace Configurations;

int main()
{
    ConfigurationProvider* cp = new ConfigurationProvider("parameters.config");
}