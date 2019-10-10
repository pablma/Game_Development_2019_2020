import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt


# Function to load a csv file
def carga_csv(file_name):
    """ carga el fichero csv especificado y lo devuelve en un array de numpy """
 
    valores = read_csv(file_name, header=None).values
    
    # we are going to work with floats always
    return valores.astype(float)


# Gets the 0 index of an array
def get_grades(data):
    return data[:, :-1]


#Gets the 1 index of an array
def get_admission(data):
    return data[:, -1]
     

def get_graph(data):

    grades = get_grades(data)
    admissions = get_admission(data)

    # gets an array with the index of the positive examples
    pos = np.where(admissions == 1)
    # gets an array with the index of the negative examples
    neg = np.where(admissions == 0)

    plt.figure()
    # Draws the positive and negative examples
    plt.scatter(grades[pos, 0], grades[pos, 1], marker='+', c='red')
    plt.scatter(grades[neg, 0], grades[neg, 1], c='blue')
    plt.show()


def sigmoid_func(data):
    exps = np.exp(data)
    
    
    """
    rows = exps.shape[0]
    cols = exps.shape[1]

    sig_a = np.ndarray(shape=(rows, cols))

    
    for i in range(rows):
        for j in range(cols):
            sig_a[rows, cols] = 1 / 1 + exps[rows + cols]
    
    return sig_a
    """

data1 = carga_csv("ex2data1.csv")
#get_graph(data1)
a = 3
print(sigmoid_func(a))
