#include "Errors.hpp"

using namespace benjft;

#pragma region AN_ERROR_IMPL
template <typename T>
AnError<T>::AnError(std::string src, std::string func, int line, std::string message) {
    this->_src     = src;
    this->_func    = func;
    this->_line    = line;
    this->_message = message;
};

template <typename T>
AnError<T>::AnError(std::string src, std::string func, int line, std::string message, int errorCode) {
    this->_src       = src;
    this->_func      = func;
    this->_line      = line;
    this->_message   = message;
    this->_errorCode = errorCode;
};

template <typename T>
AnError<T>::AnError(std::string src, std::string func, int line, std::string message, an_error_t<T> inner) {
    this->_src     = src;
    this->_func    = func;
    this->_line    = line;
    this->_message = message;
    this->_inner   = inner;
};

template <typename T>
AnError<T>::AnError(std::string src, std::string func, int line, std::string message, int errorCode, an_error_t<T> inner) {
    this->_src       = src;
    this->_func      = func;
    this->_line      = line;
    this->_message   = message;
    this->_errorCode = errorCode;
    this->_inner     = inner;
};

template <typename T> 
T AnError<T>::Value() const {
    return default;
};

template <typename T> 
bool AnError<T>::HasErrored() const {
    return true;
};

template <typename T> 
std::string AnError<T>::ErrorMessage() const {
    return this->_src + ":" + std::to_string(this->_line) + " " + 
        this->_func + "() : " + this->_message;
};

template <typename T>
an_error_t<T> AnError<T>::InnerError() const {
    return this->_inner;
};

template <typename T> 
int AnError<T>::ErrorCode() const {
    return this->_errorCode;
};

template <typename T>
template <class U>
may_error_t<U> AnError<T>::Apply(std::function<may_error_t<U>(T)> func) const {
    return this->convert<U>();
};

template <typename T>
template <class U>
may_error_t<U> AnError<T>::Apply(std::function<U(T)> func) const {
    return this->convert<U>();
};

template <typename T>
template <typename U>
an_error_t<U> AnError<T>::convert() {
    an_error_t<U> newInner = nullptr;
    if (this->_inner != nullptr) {
        newInner = this->_inner->convert<U>();
    }

    return std::make_shared<AnError<U>>(this->src, this->func, this->line, this->message, this->errorCode, newInner);
};
#pragma endregion AN_ERROR_IMPL

#pragma region JUST_IMPL    
template<typename T>
Just<T>::Just(T value) {
    this->_value = value;
};

template<typename T>
T Just<T>::Value() const {
    return this->_value;
};

template<typename T>
bool Just<T>::HasErrored() const {
    return false;
};

template<typename T>
std::string Just<T>::ErrorMessage() const {
    return "";
};

template<typename T>
an_error_t<T> Just<T>::InnerError() const {
    return nullptr;
};

template<typename T>
int Just<T>::ErrorCode() const {
    return 0;
};

template<typename T>
template <typename U>
may_error_t<U> Just<T>::Apply(std::function<may_error_t<U>(T)> func) const {
    return func(this->Value());
};

template<typename T>
template <typename U>
may_error_t<U> Just<T>::Apply(std::function<U(T)> func) const {
    U ret = func(this->Value());
    Just<U> just(ret);
    return just;
};

#pragma endregion JUST_IMPL
