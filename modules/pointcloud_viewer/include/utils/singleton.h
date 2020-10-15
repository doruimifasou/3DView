//
//  singleton.h
//  automap_core
//
//  Created by joseph on 2017/10/18.
//  Copyright © 2017年 joseph. All rights reserved.
//

#ifndef Singleton_h
#define Singleton_h

#include <mutex>
#include <functional>
#include <memory>
#include <utility>

using std::call_once;
using std::once_flag;

// This is from boost/utility.hpp
// if you don't mind having dependency on boost, get rid of this, and replace it with boost::noncopyable
namespace noncopyable_  // protection from unintended ADL
{
    class noncopyable
    {
    protected:
        noncopyable() {}
        ~noncopyable() {}
    private:  // emphasize the following members are private
        noncopyable( const noncopyable& );
        const noncopyable& operator=( const noncopyable& );
    };
}

typedef noncopyable_::noncopyable noncopyable;


template <class T>
class Singleton : private noncopyable {
public:
    template <typename... Args>
    static T& getInstance(Args&&... args) {
        
        call_once(
                  get_once_flag(),
                  [] (Args&&... args) {
                      instance_.reset(new T(std::forward<Args>(args)...));
                  }, std::forward<Args>(args)...);
        /*
         c++11 standard does specify the following syntax to be valid... but it is not supported by gcc-4.8 yet.
         Final Committee Draft, section 5.1.2.23:
         A capture followed by an ellipsis is a pack expansion (14.5.3). [ Example:
         template<class... Args> void f(Args... args) {
         auto lm = [&, args...] { return g(args...); }; lm();
         }
         — end example ]
         call_once(
         get_once_flag(),
         [&, args...] () {
         instance_.reset(new T(std::forward<Args>(args)...));
         });
         */
        return *instance_.get();
    }
    
protected:
    explicit Singleton<T>() {}
    ~Singleton<T>() {}
    
private:
    static std::unique_ptr<T> instance_;
    static once_flag& get_once_flag() {
        static once_flag once_;
        return once_;
    }
};

template<class T> std::unique_ptr<T> Singleton<T>::instance_ = nullptr;

#endif /* Singleton_h */
