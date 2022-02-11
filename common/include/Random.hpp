/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>
#include <chrono>

template<typename T>
class Random {
    public:
        Random(T start, T end) : _engine(std::chrono::high_resolution_clock::now().time_since_epoch().count()), _distrib(start, end) {}

        ~Random() {}

        T rand()
        {
            return (_distrib(_engine));
        }

    protected:
    private:
        std::default_random_engine _engine;
        std::uniform_real_distribution<double> _distrib;
};

#endif /* !RANDOM_HPP_ */
