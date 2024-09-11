import argparse
import unittest
from unittest.mock import patch


def get_arguments():  # 获取命令行参数
    parser = argparse.ArgumentParser()
    parser.add_argument('original_file', type=str)  # 原文文件地址存在args.original_file
    parser.add_argument('plagiarized_file', type=str)  # 抄袭文件地址存在args.plagiarized_file
    parser.add_argument('answer_file', type=str)  # 答案文件地址存在args.answer_file
    return parser.parse_args()


class TestGetArguments(unittest.TestCase):
    @patch('sys.argv', ['script_name', 'original.txt', 'plagiarized.txt', 'answer.txt'])
    def test_1(self):
        args = get_arguments()
        self.assertEqual(args.original_file, 'original.txt')
        self.assertEqual(args.plagiarized_file, 'plagiarized.txt')
        self.assertEqual(args.answer_file, 'answer.txt')

    @patch('sys.argv', ['script_name', 'file1.txt', 'file2.txt', 'file3.txt'])
    def test_2(self, ):
        args = get_arguments()
        self.assertEqual(args.original_file, 'file1.txt')
        self.assertEqual(args.plagiarized_file, 'file2.txt')
        self.assertEqual(args.answer_file, 'file3.txt')


if __name__ == '__main__':
    unittest.main()

# cd C:\Users\26973\Desktop\Tools\Python Code\SEPersonalProject
# coverage run test_get_arguments.py
# coverage report
