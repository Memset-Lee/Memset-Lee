import unittest
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity


def get_ans(text1, text2):  # 计算相似度
    tfidf_matrix = TfidfVectorizer().fit_transform(
        [text1, text2])  # 将文本数据转换为TF-IDF特征矩阵保存到tfidf_matrix
    return cosine_similarity(tfidf_matrix[0], tfidf_matrix[1])[0][0] * 100  # 计算相似度


class TestGetAns(unittest.TestCase):
    def test_1(self):
        self.assertAlmostEqual(get_ans('我 是 一名 学生', '我 是 一名 老师'), 33.609692727625756)

    def test_2(self):
        self.assertAlmostEqual(get_ans('我 喜欢 吃饭', '我 不 喜欢 吃面'), 33.609692727625756)


if __name__ == '__main__':
    unittest.main()

# cd C:\Users\26973\Desktop\Tools\Python Code\SEPersonalProject
# coverage run test_get_ans.py
# coverage report
