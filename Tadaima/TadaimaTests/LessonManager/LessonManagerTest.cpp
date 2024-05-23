﻿#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lessons/LessonManager.h"
#include "MockDatabase.h"

using namespace tadaima;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgReferee;

class LessonManagerTest : public ::testing::Test
{
public:
    LessonManagerTest()
    {

    }

protected:
    MockDatabase mockDatabase;
    LessonManager lessonManager{ mockDatabase };
};

TEST_F(LessonManagerTest, AddLesson)
{
    Word word1;
    word1.kana = "as";
    word1.translation = "translation1";
    word1.romaji = "romaji1";
    word1.exampleSentence = "example1";
    word1.tags = { "tag1" };

    Word word2;
    word2.kana = "qwe";
    word2.translation = "translation2";
    word2.romaji = "romaji2";
    word2.exampleSentence = "example2";
    word2.tags = { "tag2" };

    Lesson lesson;
    lesson.mainName = "Main Name";
    lesson.subName = "Sub Name";
    lesson.words = { word1, word2 };

    EXPECT_CALL(mockDatabase, addLesson("Main Name", "Sub Name")).WillOnce(Return(1));
    EXPECT_CALL(mockDatabase, addWord(1, word1)).WillOnce(Return(2));
    EXPECT_CALL(mockDatabase, addTag(2, "tag1"));
    EXPECT_CALL(mockDatabase, addWord(1, word2)).WillOnce(Return(3));
    EXPECT_CALL(mockDatabase, addTag(3, "tag2"));

    int lessonId = lessonManager.addLesson(lesson);

    EXPECT_EQ(lessonId, 1);
}

TEST_F(LessonManagerTest, AddLessons)
{
    Word word1;
    word1.tags = { "tag1" };

    Word word2;
    word2.tags = { "tag2" };

    Lesson lesson1;
    lesson1.mainName = "Main Name 1";
    lesson1.subName = "Sub Name 1";
    lesson1.words = { word1 };

    Lesson lesson2;
    lesson2.mainName = "Main Name 2";
    lesson2.subName = "Sub Name 2";
    lesson2.words = { word2 };

    std::vector<Lesson> lessons = { lesson1, lesson2 };

    EXPECT_CALL(mockDatabase, addLesson("Main Name 1", "Sub Name 1")).WillOnce(Return(1));
    EXPECT_CALL(mockDatabase, addWord(1, word1)).WillOnce(Return(2));
    EXPECT_CALL(mockDatabase, addTag(2, "tag1"));
    EXPECT_CALL(mockDatabase, addLesson("Main Name 2", "Sub Name 2")).WillOnce(Return(3));
    EXPECT_CALL(mockDatabase, addWord(3, word2)).WillOnce(Return(4));
    EXPECT_CALL(mockDatabase, addTag(4, "tag2"));

    lessonManager.addLessons(lessons);
}

TEST_F(LessonManagerTest, RenameLessons)
{
    Lesson lesson1{ 1, "Main Name 1", "Sub Name 1", {} };
    Lesson lesson2{ 2, "Main Name 2", "Sub Name 2", {} };

    std::vector<Lesson> lessons = { lesson1, lesson2 };

    EXPECT_CALL(mockDatabase, updateLesson(1, "Main Name 1", "Sub Name 1"));
    EXPECT_CALL(mockDatabase, updateLesson(2, "Main Name 2", "Sub Name 2"));

    lessonManager.renameLessons(lessons);
}

TEST_F(LessonManagerTest, GetAllLessons)
{
    std::vector<Lesson> lessons = {
        {1, "Main Name 1", "Sub Name 1", {}},
        {2, "Main Name 2", "Sub Name 2", {}}
    };

    EXPECT_CALL(mockDatabase, getAllLessons()).WillOnce(Return(lessons));

    auto result = lessonManager.getAllLessons();

    EXPECT_EQ(result, lessons);
}
