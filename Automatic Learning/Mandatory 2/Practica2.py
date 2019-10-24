import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt
import scipy.optimize as opt
from sklearn.preprocessing import PolynomialFeatures


def main():

    """
    # PART 1

    data1 = carga_csv("ex2data1.csv")
    
    grades = get_grades(data1)
    admissions = get_admission(data1)

    theta = np.zeros(grades.shape[1] + 1) 

    grades = np.hstack([np.ones([grades.shape[0], 1]), grades])

    #_gradient = gradient(theta, grades, admissions)
    #_cost = cost(theta, grades, admissions)

    opt_theta = optimize_params(theta, grades, admissions)     
    
    _cost = cost(opt_theta, grades, admissions)
   
    pinta_frontera_recta(grades, admissions, opt_theta)
 
    perc = evaluate_log_reg(opt_theta, grades, admissions)
    """

    
    # PART 2
    
    data2 = carga_csv("ex2data2.csv")
    
    grades = get_grades(data2)
    admissions = get_admission(data2)

    l = 1

    poly = PolynomialFeatures(degree=6)
    grades_ = poly.fit_transform(grades)
    

    theta = np.zeros(grades_.shape[1]) 

    #_reg_cost = reg_cost(theta, grades, admissions, l)
    #print(_reg_cost)

    opt_reg_theta = optimize_reg_params(theta, grades_, admissions, l)

    _reg_cost = reg_cost(opt_reg_theta, grades_, admissions, l) 
    
    plot_decisionboundary(grades_, admissions, opt_reg_theta, poly)
    


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
     

def visualize_data(grades, admissions):
    # gets an array with the index of the positive examples
    pos = np.where(admissions == 1)
    # gets an array with the index of the negative examples
    neg = np.where(admissions == 0)

    plt.scatter(grades[pos, 0], grades[pos, 1], marker='+', c='red')
    plt.scatter(grades[neg, 0], grades[neg, 1], c='blue')

    plt.show()
    plt.close()


def pinta_frontera_recta(x_samples, y_samples, theta):
 
    plt.figure()
    
    _x = x_samples[:, 1:x_samples.shape[1]]

    # gets an array with the index of the positive examples
    pos = np.where(y_samples == 1)
    # gets an array with the index of the negative examples
    neg = np.where(y_samples == 0)

    x1_min, x1_max = _x[:, 0].min(), _x[:, 0].max()
    x2_min, x2_max = _x[:, 1].min(), _x[:, 1].max()


    xx1, xx2 = np.meshgrid(np.linspace(x1_min, x1_max),
    np.linspace(x2_min, x2_max))


    h = sigmoid_func(np.c_[np.ones((xx1.ravel().shape[0], 1)),  xx1.ravel(), xx2.ravel()]@theta)
    h = h.reshape(xx1.shape)

    plt.scatter(_x[pos, 0], _x[pos, 1], marker='+', c='red')
    plt.scatter(_x[neg, 0], _x[neg, 1], c='blue')

    # el cuarto parámetro es el valor de z cuya frontera se
    # quiere pintar
    plt.contour(xx1, xx2, h, [0.5], linewidths=1, colors='blue')
    plt.savefig("frontera.pdf")
    plt.show()
    plt.close()


def plot_decisionboundary(x_samples, y_samples, theta, poly):
    
    plt.figure()

    _x = x_samples[:, 1:x_samples.shape[1]]

    x1_min, x1_max = _x[:, 0].min(), _x[:, 0].max()
    x2_min, x2_max = _x[:, 1].min(), _x[:, 1].max()

    xx1, xx2 = np.meshgrid(np.linspace(x1_min, x1_max), np.linspace(x2_min, x2_max))

    h = sigmoid_func(poly.fit_transform(np.c_[xx1.ravel(), xx2.ravel()]).dot(theta))
    
    h = h.reshape(xx1.shape)
    
    plt.contour(xx1, xx2, h, [0.5], linewidths=1, colors='g')
    
    plt.savefig("boundary.pdf")

    visualize_data(_x, y_samples)


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


main()