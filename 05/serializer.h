#pragma once
#include <iostream>


enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
    std::ostream& out_;

 public:
    Serializer(std::ostream& out) : out_(out) {
    }

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args&&... args) {
        return process(std::forward<Args>(args)...);
    }

 private:
    template<class T>
    Error process(T&& arg) {
        return save_(arg);
    }

    template<class T, class... Args>
    Error process(T&& arg, Args&&... args) {
        if (save_(arg) == Error::CorruptedArchive) {
            std::cout << arg << std::endl;
            return Error::CorruptedArchive;
        }
        return process(std::forward<Args>(args)...);
    }

    template<class T>
    Error save_(T&&) {
        return Error::CorruptedArchive;
    }

    Error save_(uint64_t arg) {
        out_ << arg << Separator;
        return Error::NoError;
    }

    Error save_(bool arg) {
        if (arg)
            out_ << "true";
        else
            out_ << "false";
        out_ << Separator;

        return Error::NoError;
    }
};

class Deserializer {
    static constexpr char Separator = ' ';
    std::istream& in_;

 public:
    explicit Deserializer(std::istream& in) : in_(in) {
    }

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args&&... args) {
        return process(std::forward<Args>(args)...);
    }
    
 private:
    template<class T>
    Error process(T&& arg) {
        return load_(arg);
    }

    template<class T, class... Args>
    Error process(T&& arg, Args&&... args) {
        if (load_(arg) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        return process(std::forward<Args>(args)...);
    }

    template<class T>
        Error load_(T&) {
        return Error::CorruptedArchive;
    }

    Error load_(uint64_t& arg) {
        std::string str;
        in_ >> str;

        try {
            arg = stoull(str);
        } catch (std::logic_error&) {
            return Error::CorruptedArchive;
        }

        return Error::NoError;
    }

    Error load_(bool& arg) {
        std::string str;
        in_ >> str;

        if (str == "true")
            arg = true;
        else if (str == "false")
            arg = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }
};
