"""
This script is what created the dataset pickled.

1) You need to download this file and put it in the same directory as this file.
https://github.com/moses-smt/mosesdecoder/raw/master/scripts/tokenizer/tokenizer.perl . Give it execution permission.

2) Get the dataset from http://ai.stanford.edu/~amaas/data/sentiment/ and extract it in the current directory.

3) Then run this script.
"""

dataset_path='/search/yonghuahu/dm_/project/lstm/image_data/'

import numpy
import cPickle as pkl

from collections import OrderedDict

import glob
import os

from subprocess import Popen, PIPE

# tokenizer.perl is from Moses: https://github.com/moses-smt/mosesdecoder/tree/master/scripts/tokenizer
tokenizer_cmd = ['perl','tokenizer.pl', '-l', 'en', '-q', '-']


def tokenize(sentences):

    print 'Tokenizing..',
    text = "\n".join(sentences)
    tokenizer = Popen(tokenizer_cmd, stdin=PIPE, stdout=PIPE)
    tok_text, _ = tokenizer.communicate(text)
    toks = tok_text.split('\n')[:-1]
    print 'Done'

    return toks


def build_dict(path):
    sentences = []
    currdir = os.getcwd()
    os.chdir('%s/pos/' % path)
    for ff in glob.glob("*.utf8"):
        with open(ff, 'r') as f:
            for line in f.readlines():
                line = line.strip()
                sentences.append(line)
        f.close()
    os.chdir('%s/neg/' % path)
    for ff in glob.glob("*.utf8"):
        with open(ff, 'r') as f:
            for line in f.readlines():
                line = line.strip()
                sentences.append(line)
        f.close()
    os.chdir(currdir)

    sentences = tokenize(sentences)

    print 'Building dictionary..',
    wordcount = dict()
    for ss in sentences:
        #print ss.decode("utf8").encode("gbk")
        words = ss.decode("utf8").encode("gbk").strip().lower().split()
        for w in words:
            if w not in wordcount:
                wordcount[w] = 1
            else:
                wordcount[w] += 1

    counts = wordcount.values()
    keys = wordcount.keys()

    sorted_idx = numpy.argsort(counts)[::-1]

    worddict = dict()

    for idx, ss in enumerate(sorted_idx):
        worddict[keys[ss]] = idx+2  # leave 0 and 1 (UNK)

    print numpy.sum(counts), ' total words ', len(keys), ' unique words'

    ## {word:frequecy}
    return worddict


def grab_data(path, dictionary):
    sentences = []
    currdir = os.getcwd()
    os.chdir(path)
    for ff in glob.glob("*.utf8"):
        with open(ff, 'r') as f:
            for line in f.readlines():
                line = line.strip()
                sentences.append(line)
            #sentences.append(f.readline().strip())
        f.close()
    os.chdir(currdir)
    sentences = tokenize(sentences)
    #print "size of sentences : ", len(sentences)
    seqs = [None] * len(sentences)
    for idx, ss in enumerate(sentences):
        words = ss.decode("utf8").encode("gbk").strip().lower().split()
        seqs[idx] = [dictionary[w] if w in dictionary else 1 for w in words]
	
	#print "length of seqs = ",len(seqs)
    return seqs


def main():
    # Get the dataset from http://ai.stanford.edu/~amaas/data/sentiment/
    path = dataset_path
	# dictionary = {keys:frequency}
    dictionary = build_dict(os.path.join(path, 'train'))

    ## test_x_pos, test_x_neg
    ## Frequency of test words, that in hash dictionary.
    test_x_pos = grab_data(path+'test/pos', dictionary)
    test_x_neg = grab_data(path+'test/neg', dictionary)
    test_x = test_x_pos + test_x_neg
    test_y = [1] * len(test_x_pos) + [0] * len(test_x_neg)
    print "length of test samples: ",len(test_x)
    f = open('test.pkl', 'wb')
    pkl.dump((test_x, test_y), f, -1)
    f.close()

    f = open('test.dict.pkl', 'wb')
    pkl.dump(dictionary, f, -1)
    f.close()

if __name__ == '__main__':
    main()
