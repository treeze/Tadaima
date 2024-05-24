#include "QuizWidget.h"
#include <thread>
#include <chrono>

namespace tadaima
{
    namespace gui
    {
        namespace widget
        {
            QuizWidget::QuizWidget(tools::Logger& logger, const std::vector<Lesson>& lessons)
                : m_logger(logger), quizGame(logger, lessons)
            {
                quizGame.start();
                bufferedQuestion = quizGame.getCurrentQuestion();
                bufferedOptions = quizGame.getCurrentOptions();
            }

            void QuizWidget::highlightAndAdvance()
            {
                highlightCorrectAnswer = true;
                highlightStartTime = std::chrono::steady_clock::now();
                correctAnswerIndex = quizGame.getCorrectAnswerIndex();
            }

            void QuizWidget::draw()
            {
                if( isQuizWindowOpen )
                {
                    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

                    if( ImGui::Begin("Quiz Game", &isQuizWindowOpen, ImGuiWindowFlags_NoCollapse) )
                    {
                        ImGui::TextWrapped("Welcome to the Quiz Game! Test your knowledge by selecting the correct translation.");

                        if( !highlightCorrectAnswer )
                        {
                            bufferedQuestion = quizGame.getCurrentQuestion();
                            bufferedOptions = quizGame.getCurrentOptions();
                        }

                        if( !quizGame.isFinished() )
                        {
                            ImGui::Separator();
                            ImGui::Text("%s", bufferedQuestion.c_str());

                            ImGui::Spacing();

                            for( int i = 0; i < bufferedOptions.size(); ++i )
                            {
                                char optionLabel = 'a' + i;
                                if( highlightCorrectAnswer && i == correctAnswerIndex )
                                {
                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green for correct answer
                                    ImGui::Button((std::string(1, optionLabel) + ") " + bufferedOptions[i]).c_str(), ImVec2(550, 0));
                                    ImGui::PopStyleColor();
                                }
                                else
                                {
                                    if( ImGui::Button((std::string(1, optionLabel) + ") " + bufferedOptions[i]).c_str(), ImVec2(550, 0)) )
                                    {
                                        if( !highlightCorrectAnswer )
                                        {
                                            selectedOption = optionLabel;
                                            highlightAndAdvance();
                                        }
                                    }
                                }
                            }

                            if( highlightCorrectAnswer )
                            {
                                auto now = std::chrono::steady_clock::now();
                                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - highlightStartTime).count();
                                if( elapsed >= 2 )
                                {
                                    highlightCorrectAnswer = false;
                                    quizGame.advance(selectedOption);
                                    if( !quizGame.isFinished() )
                                    {
                                        bufferedQuestion = quizGame.getCurrentQuestion();
                                        bufferedOptions = quizGame.getCurrentOptions();
                                    }
                                    selectedOption = '\0'; // Clear the selected option
                                }
                            }

                            ImGui::Text("Progress: %d/%d", quizGame.getCurrentQuestionIndex() + 1, quizGame.getTotalQuestions());

                        }
                        else
                        {
                            ImGui::Text("%s", quizGame.getResults().c_str());
                            if( ImGui::Button("Restart", ImVec2(550, 0)) )
                            {
                                quizGame.start();
                                bufferedQuestion = quizGame.getCurrentQuestion();
                                bufferedOptions = quizGame.getCurrentOptions();
                            }
                        }

                        if( ImGui::Button("Close", ImVec2(550, 0)) )
                        {
                            isQuizWindowOpen = false;
                        }
                    }

                    ImGui::End();
                }
            }
        }
    }
}