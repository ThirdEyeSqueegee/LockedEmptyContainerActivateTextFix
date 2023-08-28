#include "Hooks.h"

#include "Settings.h"

namespace Hooks
{
    void Install() noexcept
    {
        stl::write_vfunc<RE::TESObjectCONT, GetActivateText>();
        logger::info("Installed TESObjectCONT::GetActivateText hook");
    }

    bool GetActivateText::Thunk(RE::TESObjectCONT* a_this, RE::TESObjectREFR* a_activator, RE::BSString& a_dst) noexcept
    {
        const auto result{ func(a_this, a_activator, a_dst) };

        logger::debug("a_this: {} (0x{:x})", a_this->GetName(), a_this->GetFormID());
        logger::debug("a_activator: {} (0x{:x})", a_activator->GetName(), a_activator->GetFormID());

        const std::string activate_text{ a_dst.c_str() };
        const std::regex  p{ "Empty" };

        if (a_activator->IsLocked() && std::regex_search(activate_text, p))
        {
            logger::debug(R"(Replacing "Empty" with {} in activate text)", Settings::replacement_text);
            a_dst = std::regex_replace(activate_text, p, Settings::replacement_text);
        }

        return result;
    }
} // namespace Hooks
