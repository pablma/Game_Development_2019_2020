import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt


def main():
    data1 = carga_csv("ex2data1.csv")
    
    grades = get_grades(data1)
    admissions = get_admission(data1)

    theta = np.zeros(grades.shape[1] + 1)

    grades = np.hstack([np.ones([grades.shape[0], 1]), grades])

    print(gradient(theta, grades, admissions))
    print(cost(theta, grades, admissions))


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
     

def get_graph(data, grades, admissions):

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
    return 1 / 1 + np.exp(-data)


def cost(theta, x_samples, y_samples):
    m = x_samples.shape[0]

    print(1 - (sigmoid_func(x_samples @ theta)))

    return np.dot((-1 / m) , (np.transpose((np.log(sigmoid_func(x_samples @ theta)))) @ y_samples + (np.transpose(np.log(1 - sigmoid_func(x_samples @ theta)))) @ (1 - y_samples))) 


def gradient(theta, x_samples, y_samples):
    m = x_samples.shape[0]

    return (x_samples.T @ (sigmoid_func(x_samples @ theta) - y_samples)) / m


main()