/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#ifndef NDEBUG
#define LOG(x) (std::cout << x)
#define LOG_ERR(x) (std::cerr << x)
#else
#define LOG(x) ((void)0)
#define LOG_ERR(x) ((void)0)
#endif
