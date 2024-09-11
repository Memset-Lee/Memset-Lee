import unittest
from unittest.mock import mock_open, patch


def write_file(file_path, text):  # 写入文件内容
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(f'{text:.2f}')


class TestWriteFile(unittest.TestCase):
    @patch('builtins.open', new_callable=mock_open)
    def test_1(self, mock_opener):
        write_file('dummy_path.txt', 12.34)
        mock_opener().write.assert_called_once_with('12.34')

    @patch('builtins.open', new_callable=mock_open)
    def test_2(self, mock_opener):
        write_file('dummy_path.txt', 12.345)
        mock_opener().write.assert_called_once_with('12.35')


if __name__ == '__main__':
    unittest.main()

# cd C:\Users\26973\Desktop\Tools\Python Code\SEPersonalProject
# coverage run test_write_file.py
# coverage report
