/**
 * @file ApplicationSettingsWidget.h
 * @brief Defines the ApplicationSettingsWidget class for managing application settings in the GUI.
 */

#pragma once

#include "PackageType.h"
#include "Tools/DataPackage.h"
#include <cstring>
#include <string>
#include "lessons/Lesson.h"

namespace tools { class Logger; }

namespace tadaima
{
    namespace gui
    {
        namespace widget
        {

            /**
             * @brief Enum for package keys.
             */
            enum class LessonPackageKey : uint32_t
            {
                Type,
                LessonsPackage
            };

            /**
             * @brief Enum for package types.
             */
            enum class LessonPackageType : uint32_t
            {
                LessonCreated,
                LessonModified,
                LessonDeleted
            };

            /**
             * @brief Enum for lesson data keys.
             */
            enum class LessonDataKey : uint32_t
            {
                id,
                MainName,
                SubName,
                Words
            };

            /**
             * @brief Enum for word data keys.
             */
            enum class LessonWordDataKey : uint32_t
            {
                id,
                Kana,
                Translation,
                Romaji,
                ExampleSentence,
                Tags
            };

            /**
             * @brief Alias for word data package.
             */
            using WordDataPackage = tools::ComplexDataPackage<LessonWordDataKey, int, std::string, std::vector<std::string>>;

            /**
             * @brief Alias for lesson package.
             */
            using LessonPackage = tools::ComplexDataPackage<LessonDataKey, int, std::string, std::vector<WordDataPackage>>;

            /**
             * @brief Represents a package containing lesson data.
             */
            class LessonDataPackage : public tools::ComplexDataPackage<LessonPackageKey, LessonPackageType, std::vector<LessonPackage>>
            {
            public:

                /**
                 * @brief Constructs a LessonDataPackage object with the given identifier.
                 * @param id The identifier of the package.
                 */
                LessonDataPackage() : ComplexDataPackage(PackageType::Lessons) {}

                /**
                * Desc
                *
                * @param File name.
                * @return EN_ErrorCode::EC_NoError if everything was fine.
                */
                std::vector<Lesson> decode() const
                {
                    std::vector<Lesson> lessons;
                    auto lessonPackages = get<std::vector<LessonPackage>>(LessonPackageKey::LessonsPackage);

                    for( const auto& lessonPackage : lessonPackages )
                    {
                        Lesson lesson;
                        lesson.id = lessonPackage.get<int>(LessonDataKey::id);
                        lesson.mainName = lessonPackage.get<std::string>(LessonDataKey::MainName);
                        lesson.subName = lessonPackage.get<std::string>(LessonDataKey::SubName);

                        auto wordPackages = lessonPackage.get<std::vector<WordDataPackage>>(LessonDataKey::Words);
                        for( const auto& wordPackage : wordPackages )
                        {
                            Word word;
                            word.id = wordPackage.get<int>(LessonWordDataKey::id);
                            word.kana = wordPackage.get<std::string>(LessonWordDataKey::Kana);
                            word.translation = wordPackage.get<std::string>(LessonWordDataKey::Translation);
                            word.romaji = wordPackage.get<std::string>(LessonWordDataKey::Romaji);
                            word.exampleSentence = wordPackage.get<std::string>(LessonWordDataKey::ExampleSentence);
                            word.tags = wordPackage.get<std::vector<std::string>>(LessonWordDataKey::Tags);

                            lesson.words.push_back(word);
                        }

                        lessons.push_back(lesson);
                    }

                    return lessons;
                }
            };
        }
    }
}
