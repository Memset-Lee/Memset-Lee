import unittest
from unittest.mock import mock_open, patch


def read_file(file_path):  # 读取文件内容
    with open(file_path, 'r', encoding='utf-8') as file:
        return file.read()


class TestReadFile(unittest.TestCase):
    @patch('builtins.open', new_callable=mock_open, read_data='我是一名学生。')
    def test_1(self, mock_opener):
        self.assertEqual(read_file('dummy_path.txt'), '我是一名学生。')

    @patch('builtins.open', new_callable=mock_open, read_data='123，456，789')
    def test_2(self, mock_opener):
        self.assertEqual(read_file('dummy_path.txt'), '123，456，789')


if __name__ == '__main__':
    unittest.main()

# cd C:\Users\26973\Desktop\Tools\Python Code\SEPersonalProject
# coverage run test_read_file.py
# coverage report
