import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt
import scipy.optimize as opt


def main():
    data1 = carga_csv("ex2data1.csv")
    
    grades = get_grades(data1)
    admissions = get_admission(data1)

    theta = np.zeros(grades.shape[1] + 1) 

    grades = np.hstack([np.ones([grades.shape[0], 1]), grades])

    #_gradient = gradient(theta, grades, admissions)
    #_cost = cost(theta, grades, admissions)

    opt_theta = optimize_params(theta, grades, admissions)     
    
    _cost = cost(opt_theta, grades, admissions)
    print(_cost)
    
    #get_graph(grades, admissions, opt_theta)  


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
     

def get_graph(grades, admissions, theta):

    gr = grades[:, 1:grades.shape[1]]

    # gets an array with the index of the positive examples
    pos = np.where(admissions == 1)
    # gets an array with the index of the negative examples
    neg = np.where(admissions == 0)

    plt.figure()
    # Draws the positive and negative examples
    plt.scatter(gr[pos, 0], gr[pos, 1], marker='+', c='red')
    plt.scatter(gr[neg, 0], gr[neg, 1], c='blue')
    plt.plot([30, 90], [theta[0] + theta[1] * 30, theta[0] + theta[1] * 90])
    plt.show()


def sigmoid_func(data):
    return 1 / (1 + np.exp(-data))


def cost(theta, x_samples, y_samples):
    m = x_samples.shape[0]

    return np.dot((-1 / m) , (np.transpose((np.log(sigmoid_func(x_samples @ theta)))) @ y_samples + (np.transpose(np.log(1 - sigmoid_func(x_samples @ theta)))) @ (1 - y_samples))) 


def gradient(theta, x_samples, y_samples):
    m = x_samples.shape[0]

    return (x_samples.T @ (sigmoid_func(x_samples @ theta) - y_samples)) / m


def optimize_params(theta, x_samples, y_samples):
    result = opt.fmin_tnc(func=cost, x0=theta, fprime=gradient, args=(x_samples, y_samples))
    theta_opt = result[0]

    return theta_opt


main()