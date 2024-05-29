/**
 * @file MenuBarWidget.h
 * @brief Defines the MenuBarWidget class, representing the menu bar widget.
 */

#pragma once

#include "Widget.h"
#include "ApplicationSettingsWidget.h"

namespace tools { class Logger; }

namespace tadaima
{
    namespace gui
    {
        namespace widget
        {
            /**
             * @brief A widget representing the menu bar.
             */
            class MenuBarWidget : public Widget
            {
            public:
                /**
                 * @brief Constructs a MenuBarWidget object.
                 * @param logger Reference to a Logger instance for logging.
                 */
                MenuBarWidget(tools::Logger& logger);

                /**
                 * @brief Initializes the menu bar widget.
                 * @param r_package The data package for initialization.
                 */
                void initialize(const tools::DataPackage& package) override;

                /**
                 * @brief Draws the menu bar widget.
                 * @param p_open Pointer to a boolean indicating whether the widget is open.
                 */
                void draw(bool* p_open) override;

                /**
                 * @brief Sets the observer for the menu bar widget.
                 * @param observer The observer to set.
                 */
                void setObserver(Listener observer) override;

            private:
                tools::Logger& m_logger; /**< Reference to the Logger instance for logging. */

                /**
                 * @brief Displays the about window.
                 * @param p_open Pointer to a boolean indicating whether the window is open.
                 */
                void showAboutWindow(bool* p_open);

                bool show_settings = false; /**< Flag to track the settings window state. */
                ApplicationSettingsWidget m_ApplicationSettingsWidget; /**< The application settings widget. */
            };
        }
    }
}
