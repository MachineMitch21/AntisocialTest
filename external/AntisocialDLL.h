
#ifndef ANTISOCIAL_H
#define ANTISOCIAL_H

#ifdef __WIN32__
#ifdef ANTISOCIAL_EXPORT
#define ANTISOCIAL_API __declspec(dllexport)
#else
#define ANTISOCIAL_API __declspec(dllimport)
#endif // ANTISOCIAL_EXPORT
#endif // __WIN32__

#ifdef __LINUX__
#define ANTISOCIAL_API
#endif // __LINUX__

#endif // ANTISOCIAL_H
