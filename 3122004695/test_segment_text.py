import re
import jieba
import unittest


def segment_text(text):  # 对文本进行分词
    text_without_punctuation = re.sub(r'[^\w\s]', '', text)  # 去除标点符号
    segment_list = jieba.cut(text_without_punctuation, cut_all=False)
    text_with_spaces = " ".join(segment_list)  # 用空格分词
    return text_with_spaces


class TestSegmentText(unittest.TestCase):
    def test_1(self):
        self.assertEqual(segment_text('你好，我是计科三班的一名学生。'), '你好 我 是 计科 三班 的 一名 学生')

    def test_2(self):
        self.assertEqual(segment_text('你好我是计科三班的一名学生'), '你好 我 是 计科 三班 的 一名 学生')

    def test_3(self):
        self.assertEqual(segment_text('123，456，789'), '123456789')

    def test_4(self):
        self.assertEqual(segment_text('123456789'), '123456789')

    def test_5(self):
        self.assertEqual(segment_text('，，。。！！'), '')


if __name__ == '__main__':
    unittest.main()

# cd C:\Users\26973\Desktop\Tools\Python Code\SEPersonalProject
# coverage run test_segment_text.py
# coverage report
