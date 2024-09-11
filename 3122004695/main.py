import os
import sys
import jieba
import argparse
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity


def get_arguments():  # 获取命令行参数
    parser = argparse.ArgumentParser()
    parser.add_argument("original_file", type=str)  # 原文文件地址存在args.original_file
    parser.add_argument("plagiarized_file", type=str)  # 抄袭文件地址存在args.plagiarized_file
    parser.add_argument("answer_file", type=str)  # 答案文件地址存在args.answer_file
    return parser.parse_args()


def read_file(file_path):  # 读取文件内容
    with open(file_path, 'r', encoding='utf-8') as file:
        return file.read()


def write_file(file_path):  # 写入文件内容
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(f"{similarity:.2f}")


def segment_text(text):  # 对文本进行分词
    seg_list = jieba.cut(text, cut_all=False)
    return " ".join(seg_list)


def get_ans():  # 计算相似度
    tfidf_matrix = TfidfVectorizer().fit_transform(
        [segment_original_text, segment_plagiarized_text])  # 将文本数据转换为TF-IDF特征矩阵保存到tfidf_matrix
    return cosine_similarity(tfidf_matrix[0], tfidf_matrix[1])[0][0]  # 计算相似度


def check_file_path():  # 判断路径是否正确
    flag = 0
    for file_path in [args.original_file, args.plagiarized_file, args.answer_file]:
        if not os.path.exists(file_path):
            print(f"Path does not exist: {file_path}")
            flag = 1
    if flag == 1:
        sys.exit()


def check_empty_file():  # 判断文件是否为空
    flag = 0
    if not original_text:
        print("The original text file is empty.")
        flag = 1
    if not plagiarized_text:
        print("The plagiarized text file is empty.")
        flag = 1
    if flag == 1:
        sys.exit()


args = get_arguments()  # 获取命令行参数

check_file_path()  # 判断路径是否正确

original_text = read_file(args.original_file)  # 读取原文文件内容到original_text
plagiarized_text = read_file(args.plagiarized_file)  # 读取抄袭文件内容到plagiarized_text

check_empty_file()  # 判断文件是否为空

segment_original_text = segment_text(original_text)  # 将original_text分词保存到segment_original_text
segment_plagiarized_text = segment_text(plagiarized_text)  # 将plagiarized_text分词保存到segment_plagiarized_text

similarity = get_ans()  # 计算相似度

print(f"{similarity:.2f}")  # 在cmd中打印相似度
write_file(args.answer_file)  # 将相似度写入答案文件
