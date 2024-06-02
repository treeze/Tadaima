///**
// * @file Flashcard.h
// * @brief Declaration of the Flashcard struct for vocabulary quizzes.
// *
// * This file contains the declaration of the Flashcard struct, which represents
// * a single flashcard used in a vocabulary quiz. Each flashcard contains information
// * about a word, its associated lesson, and the user's progress with that word.
// */
//
//#pragma once
//
//#include "lessons/Lesson.h"
//#include <string>
//#include "QuizType.h"
//
//namespace tadaima
//{
//    namespace gui
//    {
//        namespace quiz
//        {
//            /**
//             * @struct Flashcard
//             * @brief A struct to represent a flashcard in a vocabulary quiz.
//             *
//             * The Flashcard struct contains information about a word, its associated lesson,
//             * and the user's progress with that word in the quiz.
//             */
//            struct Flashcard
//            {
//                Word word; ///< The word associated with the flashcard.
//                int lessonId = 0; ///< The ID of the lesson the flashcard belongs to.
//                int badAttempts = 0; ///< The number of incorrect attempts for this flashcard.
//                int goodAttemps = 0; ///< The number of correct attempts for this flashcard.
//                bool learned = false; ///< Flag indicating whether the word has been learned.
//
//                std::string getCorrectWord()
//                {
//                    std::string correctAnswer;
//
//                    switch( wordType )
//                    {
//                        case quiz::WordType::BaseWord:
//                            correctAnswer = flashcard.word.translation;
//                            break;
//
//                        case quiz::WordType::Kana:
//                            correctAnswer = flashcard.word.kana;
//                            break;
//
//                        case quiz::WordType::Romaji:
//                            correctAnswer = flashcard.word.romaji;
//                            break;
//                        default:
//                            break;
//                    }
//
//                    return correctAnswer;
//                }
//
//                quiz::WordType wordType = quiz::WordType::BaseWord;
//                quiz::WordType correctWordType = quiz::WordType::Romaji;
//
//                /**
//                 * @brief Constructor for the Flashcard struct.
//                 *
//                 * Initializes a flashcard with the provided word, lesson details, and number of bad attempts.
//                 *
//                 * @param w The word associated with the flashcard.
//                 * @param lId The ID of the lesson the flashcard belongs to.
//                 * @param attempts The number of incorrect attempts for this flashcard.
//                 */
//                Flashcard(const Word& w, int lId, int attempts)
//                    : word(w), lessonId(lId), badAttempts(attempts), learned(false)
//                {
//                }
//
//            private:
//
//                std::string getWord()
//                {
//                    std::string correctAnswer;
//
//                    switch( wordType )
//                    {
//                        case quiz::WordType::BaseWord:
//                            correctAnswer = flashcard.word.translation;
//                            break;
//
//                        case quiz::WordType::Kana:
//                            correctAnswer = flashcard.word.kana;
//                            break;
//
//                        case quiz::WordType::Romaji:
//                            correctAnswer = flashcard.word.romaji;
//                            break;
//                        default:
//                            break;
//                    }
//
//                    return correctAnswer;
//                }
//
//            };
//        }
//    }
//}
