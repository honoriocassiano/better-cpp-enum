#include <set>
#include <functional>

template <class UnderType, class Type>
class Enum {

protected:
    explicit Enum(const UnderType& value);

private:
    struct Enum_Predicate_Corresponds 
        : public std::unary_function< const Enum<UnderType, Type>*, bool > {

        // Constructor
        Enum_Predicate_Corresponds(const UnderType& _value) 
            : value(_value) {}

        bool operator()(const Enum<UnderType, Type>* e) {
            return e != nullptr && e->getValue() == value;
        }

    private:
        const UnderType* value;
    };

    struct Enum_Ptr_Less 
        : public std::binary_function<
            const Enum<UnderType, Type>*,
            const Enum<UnderType, Type>*,
            bool
            > {
        
        bool operator()(
            const Enum<UnderType, Type>* e1,
            const Enum<UnderType, Type>* e2) {

            return e1->getValue() < e2->getValue();
        }
    };

public:

    const UnderType& getValue() const {
        return value;
    }

    static const UnderType& min() {
        return (*instances.begin())->value;
    }
    
    static const UnderType& max() {
        return (*instances.rbegin())->value;
    }

    static const Enum<UnderType, Type>*
        getCorrespondingEnum(const UnderType& value) {

        auto it = find_if(instances.begin(),
            instances.end(),
            Enum_Predicate_Corresponds(value));

        return (it != instances.end()) ? *it : nullptr;
    }

    static bool isValidValue(const UnderType& value) {
        return getCorrespondingEnum(value) != nullptr;
    }

    static typename std::set<const Enum<UnderType, Type>*, Enum_Ptr_Less>::size_type size() {
        return instances.size();
    }

    static typename std::set<const Enum<UnderType, Type>*, Enum_Ptr_Less>::const_iterator begin() {
        return instances.begin();
    }

    static typename std::set<const Enum<UnderType, Type>*, Enum_Ptr_Less>::const_iterator end() {
        return instances.end();
    }

private:
    UnderType value;

    static std::set<const Enum<UnderType, Type>*, Enum_Ptr_Less> instances;
};

template<class U, class T>
inline Enum<U, T>::Enum(const U& value)
         : value(value) {

    instances.insert(this);
}