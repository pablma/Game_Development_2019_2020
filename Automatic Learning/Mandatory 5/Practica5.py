import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt
import scipy.optimize as opt
import scipy as scp
from sklearn.preprocessing import PolynomialFeatures


def main():
    data_filename = "ex5data1.mat"
    X, y, Xtest, ytest, Xval, yval = load_data(data_filename)

    theta = np.ones(X.shape)
    l = 0

    result = cost(theta, X, y, l)

    print(result)
    

def load_data(file_name):
    data = scp.io.loadmat(file_name)
    
    X = data['X']
    y = data['y']

    Xtest = data['Xtest']
    ytest = data['ytest']

    Xval = data['Xval']
    yval = data['yval']

    return X, y, Xtest, ytest, Xval, yval
     

def h(theta, x):
    return np.dot(theta.T, x)


def sigmoid(z):
    return 1 / (1 + np.exp(-z))


def cost(theta, x, y ,l):
    m = x.shape[0]
    sum1 = 0
    sum2 = 0
 
    sum1 = np.sum((h(theta, x) - y)**2)

    sum2 = np.sum((theta)**2)

    return (sum1 / (2 * m)) + ((l * (sum2)) / (2 * m))


def gradient(theta, x, y, l):
   
    """
    Compute the gradient.
    Args:
        theta: array shape(n+1, 1) 
        X: array shape(m, n+1) 
        y: array shape(m, 1)
        lambda_coef: int
    Returns:
        gradient: array shape(n+1, m)
    """
    m = x.shape[0]
    h_theta = sigmoid(np.dot(x, theta.T))
   
    # Exclude theta_0!!!
    reg_term = (l / m) * (theta[1:])
    gradient = (1 / m) * np.dot(x.T, (h_theta - y))
    print(gradient[1:].shape)
    print(reg_term.shape)
    gradient[1:] = gradient[1:] + reg_term
    return gradient
   
"""
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


def optimize_params(theta, x_samples, y_samples):
    result = opt.fmin_tnc(func=cost, x0=theta, fprime=gradient, args=(x_samples, y_samples))
    theta_opt = result[0]

    return theta_opt


def optimize_reg_params(theta, x_samples, y_samples, l):
    result = opt.fmin_tnc(func=reg_cost, x0=theta, fprime=reg_gradient, args=(x_samples, y_samples, l))
    theta_opt = result[0]

    return theta_opt


def evaluate_log_reg(theta, x_samples, y_samples):
    
    hip = (h(theta, x_samples) >= 0.5).astype(float)
    correct_clasification = (hip == y_samples)
    
    # Returns the number of elements that are true in the correct_clasification array
    clasified = sum(map(lambda x: x == True, correct_clasification))
    perc = (clasified * 100) / y_samples.shape[0]

    return perc

"""
main()