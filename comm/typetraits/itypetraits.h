#ifndef __HPM_COMM_ITYPTRAITS_ITYPTRAITS_H__
#define __HPM_COMM_ITYPTRAITS_ITYPTRAITS_H__

#if 1

/*
 *bool TypeTraits<T>::IsPODType()
 *
 * struct xxx: false
 * int,char,float: true
 **/


// 非内置类型都返回 false
template < class T >
struct TypeTraits{
    static bool IsPODType() {
        return false;
    }
};

// 内置类型返回 true
template <>
struct TypeTraits < short > {
    static bool IsPODType() {
        return true;
    }
};

template <>
struct TypeTraits < unsigned short > {
    static bool IsPODType() {
        return true;
    }
};

template <>
struct TypeTraits < int > {
    static bool IsPODType() {
        return true;
    }
};

template <>
struct TypeTraits < unsigned int > {
    static bool IsPODType() {
        return true;
    }
};

template <>
struct TypeTraits < long > {
    static bool IsPODType() {
        return true;
    }
};

template <>
struct TypeTraits < float > {
    static bool IsPODType() {
        return true;
    }
};

template <>
struct TypeTraits < double > {
    static bool IsPODType() {
        return true;
    }
};

#else
/*
 *bool TypeTraits<T>::IsPODType.Get()
 *
 * struct xxx: false
 * int,char,float: true
 * */


// 非内置类型都返回 false
struct __TrueType {
    static bool Get() {
        return true;
    }
};

struct __FalseType{
    static bool Get() {
        return true;
    }
};

// 内置类型返回 true
template < class T >
struct TypeTraits{
    typedef __FalseType IsPODType;
};

template<>
struct TypeTraits<short>{
    typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<int>{
    typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<long>{
    typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<char>{
    typedef __TrueType IsPODType;
};

#endif

#endif
