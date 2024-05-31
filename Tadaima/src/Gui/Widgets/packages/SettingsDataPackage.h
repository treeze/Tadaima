/**
 * @file ApplicationSettingsWidget.h
 * @brief Defines the ApplicationSettingsWidget class for managing application settings in the GUI.
 */

#pragma once

#include "PackageType.h"
#include "Tools/DataPackage.h"
#include <cstring>
#include <string>

namespace tools { class Logger; }

namespace tadaima
{
    namespace gui
    {
        namespace widget
        {
            /**
             * @brief Represents a package containing settings data.
             */
            class SettingsDataPackage : public tools::ComplexDataPackage<uint32_t, std::string>
            {
            public:

                /**
                 * @brief Enum class for package keys used in settings data packages.
                 */
                enum PackageKey : uint32_t
                {
                    Username,       /**< Key for username. */
                    DictionaryPath, /**< Key for dictionary path. */
                    InputWord,      /**< Key for input word. */
                    TranslatedWord  /**< Key for translated word. */
                };

                /**
                 * @brief Constructs a SettingsDataPackage object.
                 */
                SettingsDataPackage() : ComplexDataPackage(PackageType::Settings) {}
            };

        }
    }
}