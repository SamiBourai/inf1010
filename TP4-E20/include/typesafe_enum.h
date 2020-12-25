#ifndef TYPESAFEENUM_H
#define TYPESAFEENUM_H

//! Noter que pour être "type safe" l'énumération utilisée devrait être une "enum class" (C++11)
//! malgré que enum_value accepte aussi les anciennes "enum". Pour utiliser to_enum, conversion
//! sécuritaire d'un entier vers une énumération, les énumérations doivent utiliser des valeurs
//! contigues et avoir deux valeurs spéciales, first_ et last_, qui correspondent à la première
//! (plus petite) et dernière (plus grande) valeur de l'énumération.  Ceci requiert une "enum class"
//! sinon il y aura plusieurs définitions de first_ et last_.
//! \author Francois-R.Boyer@PolyMtl.ca
//! \date   2019-02

#include <cassert>
#include <type_traits>

//! Donne la valeur numérique qui correspond à une valeur d'énumération, dans le bon type
//! sous-jacent.
template<typename Enum>
constexpr auto enum_value(Enum x)
{
    static_assert(
        std::is_enum_v<Enum>); // Pas nécessaire pour avoir une erreur de compilation, la ligne
                               // ci-dessous échoue déjà si ce n'est pas une enum, mais ça permet
                               // d'avoir l'appel à cette fonction dans le message d'erreur.
    // NOTE: Devrait utiliser un "concept" C++20 au lieu de static_assert, le message d'erreur
    // devrait être encore meilleur.
    return static_cast<std::underlying_type_t<Enum>>(x);
}

//! Suppose que l'Enum contient des valeurs first_ et last_, et que toutes les valeurs entre sont
//! valides.
template<typename Enum, typename T>
constexpr bool valid_as_enum(T x)
{
    static_assert(std::is_enum_v<Enum>);
    static_assert(std::is_integral_v<T>);
    using type_used_for_comparison = decltype(T{} + std::underlying_type_t<Enum>{});
    bool can_be_represented_in_used_type = std::is_signed_v<type_used_for_comparison> || x >= T{};
    auto casted_value = static_cast<type_used_for_comparison>(x);
    return can_be_represented_in_used_type && casted_value >= enum_value(Enum::first_) &&
           casted_value <= enum_value(Enum::last_);
}

//! Suppose que l'Enum contient des valeurs first_ et last_, et que toutes les valeurs entre sont
//! valides.
template<typename Enum, typename T>
constexpr Enum to_enum(T x)
{
    assert(valid_as_enum<Enum>(x));
    return Enum(x);
}

#endif