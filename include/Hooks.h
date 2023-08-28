#pragma once

namespace Hooks
{
    void Install() noexcept;

    class GetActivateText : public Singleton<GetActivateText>
    {
    public:
        static bool Thunk(RE::TESObjectCONT* a_this, RE::TESObjectREFR* a_activator, RE::BSString& a_dst) noexcept;

        inline static REL::Relocation<decltype(&Thunk)> func;

        static constexpr std::size_t idx{ 76 };
    };
} // namespace Hooks
