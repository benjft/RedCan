#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <functional>
#include <memory>
#include <string>

#define AnError1(T, s) (std::make_shared<AnError<T>>(__FILE__, __FUNCTION__, __LINE__, s))
#define AnError2(T, s, v) (std::make_shared<AnError<T>>(__FILE__, __FUNCTION__, __LINE__, s, v))
#define AnError3(T, s, v, e) (std::make_shared<AnError<T>>(__FILE__, __FUNCTION__, __LINE__, s, v, e))

namespace benjft {
    template <typename T>
    class MayError;

    template <typename T>
    class AnError;// : public MayError<T>;

    template <typename T>
    using may_error_t = std::shared_ptr<MayError<T>>;

    template <typename T>
    using an_error_t = std::shared_ptr<AnError<T>>;

    template <typename>
    class MayError {
    protected:
        MayError() { };

    public:
        virtual T             Value() const = 0;
        virtual bool          HasErrored() const = 0;
        virtual std::string   ErrorMessage() const = 0;
        virtual an_error_t<T> InnerError() const = 0;
        virtual int           ErrorCode() const = 0;

        template <typename U>
        virtual may_error_t<U> Apply(std::function<may_error_t<U>(T)> func) const = 0;

        template <typename U>
        virtual may_error_t<U> Apply(std::function<U(T)> func) const = 0;
    };

    template <typename T>
    class AnError : public MayError<T> {
        private:
            std::string    _src;
            std::string    _func;
            int            _line;
            std::string    _message;
            int            _errorCode;
            an_error_t<T>  _inner;

            template<typename U>
            an_error_t<U> convert();

        public:
            AnError(std::string src, std::string func, int line, std::string message);
            AnError(std::string src, std::string func, int line, std::string message, int errorCode);
            AnError(std::string src, std::string func, int line, std::string message, an_error_t<T> inner);
            AnError(std::string src, std::string func, int line, std::string message, int errorCode, an_error_t<T> inner);

            virtual T Value() const;
            virtual bool HasErrored() const;
            virtual std::string ErrorMessage() const;
            virtual an_error_t<T> InnerError() const;
            virtual int ErrorCode() const;

            template <typename U>
            virtual may_error_t<U> Apply(std::function<may_error_t<U>(T)> func) const;

            template <typename U>
            virtual may_error_t<U> Apply(std::function<U(T)> func) const;
    };

    template <typename T>
    class Just : public MayError<T> {
    private:
        T _value;
    public:
        Just(T value);
        virtual T             Value() const;
        virtual bool          HasErrored() const;
        virtual std::string   ErrorMessage() const;
        virtual an_error_t<T> InnerError() const;
        virtual int           ErrorCode() const;

        template <typename U>
        virtual may_error_t<U> Apply(std::function<may_error_t<U>(T)> func) const = 0;

        template <typename U>
        virtual may_error_t<U> Apply(std::function<U(T)> func) const = 0;
    };

}

#include "Errors.tpp"

#endif //ERRORS_HPP_