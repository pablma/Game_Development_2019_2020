import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt
import scipy.optimize as opt
from sklearn.preprocessing import PolynomialFeatures
from scipy.io import loadmat



def main():
    X, y = load_file("ex3data1.mat")
    num_tags = 10
    reg = 1

    draw_samples(X, num_tags)

    X = np.hstack([np.ones([X.shape[0], 1]), X])    # Adding the ones column
    theta = np.zeros(X.shape[1])    # Theta array 

    oneVsAll(theta, X, y, num_tags, reg)
    


# Function to load a csv file
def load_file(file_name):
    
    data = loadmat(file_name)

    # almacena los datos leídos en X e y
    y = data['y']
    X = data['X']

    return X, np.ravel(y)

def draw_samples(data, numOfSamples):
    sample = np.random.choice(data.shape[0], numOfSamples)
    plt.imshow(data[sample, :].reshape(-1, 20).T)
    plt.axis('off')
      

def sigmoid_func(x):
    return 1 / (1 + np.exp(-x))


def h(theta, x):
    return sigmoid_func(x @ theta.T)


def cost(theta, x_samples, y_samples):
    m = x_samples.shape[0]
    h = sigmoid_func(x_samples @ theta)

    return np.dot((-1 / m) , (np.transpose((np.log(h))) @ y_samples + (np.transpose(np.log(1 - h))) @ (1 - y_samples))) 


def reg_cost(theta, x_samples, y_samples, l):

    _cost = cost(theta, x_samples, y_samples)
    c = np.dot(l, np.sum((theta)**2) / (np.dot(2, x_samples.shape[0])))

    return _cost + c


def gradient(theta, x_samples, y_samples):
    m = x_samples.shape[0]
    h = sigmoid_func(np.dot(x_samples, theta))

    result = np.dot(x_samples.T , (h - y_samples)) / m
    return result


def reg_gradient(theta, x_samples, y_samples, l):
    grad = gradient(theta, x_samples, y_samples)
    return grad + (l / x_samples.shape[0]) * theta


def oneVsAll(theta, X, y, num_tags, reg):

    mat = np.zeros((num_tags, theta.shape(0))
  
    for i in range(num_tags):
        y_modified = np.where(y == i, 1, 0)
        a = optimize_reg_params(theta, X, y_modified, reg)
        mat[i] = a

    return mat


def optimize_reg_params(theta, X, y, reg):
    result = opt.fmin_tnc(func=reg_cost, x0=theta, fprime=reg_gradient, args=(X, y, reg))
    theta_opt = result[0]

    return theta_opt



main()