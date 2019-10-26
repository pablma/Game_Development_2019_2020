import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt
import scipy.optimize as opt
from sklearn.preprocessing import PolynomialFeatures
from scipy.io import loadmat



def main():
    X, y = load_file("ex3data1.mat")
    draw_samples(X, 10)
    print(y)
    


# Function to load a csv file
def load_file(file_name):
    
    data = loadmat(file_name)

    # almacena los datos leídos en X e y
    y = data['y']
    X = data['X']

    return X, y

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
    h = sigmoid_func(x_samples @ theta)

    return (x_samples.T @ (h - y_samples)) / m


def reg_gradient(theta, x_samples, y_samples, l):
    grad = gradient(theta, x_samples, y_samples)
    return grad + (l * theta) / x_samples.shape[0]


def oneVsAll(X, y, num_etiquetas, reg):
    return True



def optimize_params(theta, x_samples, y_samples):
    result = opt.fmin_tnc(func=cost, x0=theta, fprime=gradient, args=(x_samples, y_samples))
    theta_opt = result[0]

    return theta_opt


def optimize_reg_params(theta, x_samples, y_samples, l):
    result = opt.fmin_tnc(func=reg_cost, x0=theta, fprime=reg_gradient, args=(x_samples, y_samples, l))
    theta_opt = result[0]

    return theta_opt



main()