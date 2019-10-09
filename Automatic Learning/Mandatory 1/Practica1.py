import numpy as np
from pandas.io.parsers import read_csv
import matplotlib.pyplot as plt


# Function to load a csv file
def carga_csv(file_name):
    """ carga el fichero csv especificado y lo devuelve en un array de numpy """
 
    valores = read_csv(file_name, header=None).values
    
    # we are going to work with floats always
    return valores.astype(float)


# np.hstack para añadir una columna de 1

# Gets the 0 index of an array
def get_x_samples(samples):
    return samples[:, :-1]


#Gets the 1 index of an array
def get_y_samples(samples):
    return samples[:, -1]


#Theta = [0, 0]     Theta0 = 0       Theta1 = 0
#Añadiendo la columna de 1's podemos obtener el valor de h con un producto de vectores haciendo [1  x] * [theta theta]
def h(x, theta):
    return np.dot(theta.T, x)


def summatory_theta0(m, theta, x_samples, y_samples):

    sum = 0

    for i in range(m):
        sum += x_samples[i][0] * h(x_samples[i], theta) - y_samples[i]

    return sum


def summatory_theta1(m, theta, x_samples, y_samples):

    sum = 0

    for i in range(m):
        sum += x_samples[i][1] * (h(x_samples[i], theta) - y_samples[i]) 

    return sum    


def summatory(m, theta, x_samples, y_samples, col):
    
    sum = 0

    for i in range(m):
        sum += x_samples[i][col] * (h(x_samples[i], theta) - y_samples[i]) 

    return sum   


def summatory_J(m, theta, x_samples, y_samples):

    sum = 0

    for i in range(m):
        sum += (h(x_samples[i], theta) - y_samples[i]) ** 2

    return sum 

    
def cost_func(theta, m, x_samples, y_samples):
    
    sum = summatory_J(m, theta, x_samples, y_samples)
    return  sum / (2 * m)


def gradient_desc(data):

    x = get_x_samples(data)
    y = get_y_samples(data)
    
    aux_x = get_x_samples(data)

    m = x.shape[0]
    n = x.shape[1]

    x = np.hstack([np.ones([m, 1]), x])

    theta = np.zeros([n + 1,], dtype='float')
    alpha = 0.01

    for i in range(1500):

        aux0 = theta[0] - (alpha / m) * summatory_theta0(m, theta, x, y)
        aux1 = theta[1] - (alpha / m) * summatory_theta1(m, theta, x, y)

        J = cost_func(theta, m, x, y)

        theta[0] = aux0
        theta[1] = aux1
        
        print(J)  


    show_graph(theta, aux_x, y)


def show_graph(theta, x_samples, y_samples):

    plt.figure()
    plt.scatter(x_samples, y_samples, c = 'red')
    plt.plot([2, 22.5], [theta[0] + theta[1] * 2, theta[0] + theta[1] * 22.5])
    plt.legend()
    plt.show()


def gradient_desc_multi_var(data):

    x = get_x_samples(data)
    y = get_y_samples(data)
    
    aux_x = get_x_samples(data)

    n_examples = x.shape[0]
    n_variables = x.shape[1]

    mat, means, devs = normalize(x)
  
    mat = np.hstack([np.ones([n_examples, 1]), mat])

    theta = np.zeros([n_variables + 1,], dtype='float')
    alpha = 0.01

      
    for i in range(1500):

        aux0 = theta[0] - (alpha / m) * summatory_theta0(m, theta, x, y)
        aux1 = theta[1] - (alpha / m) * summatory_theta1(m, theta, x, y)
        aux2 = theta[2] - (alpha / m) * summatory_theta1(m, theta, x, y)

        J = cost_func(theta, m, x, y)

        theta[0] = aux0
        theta[1] = aux1
        theta[2] = aux2
        
        print(J)  


    show_graph(theta, aux_x, y)



def normalize(mat):
    
    rows = mat.shape[0]
    cols = mat.shape[1]

    means = np.ndarray(shape=(cols), dtype=float)
    devs = np.ndarray(shape=(cols), dtype=float)
    
    for k in range(cols):
        means[k] = mat[:, k].mean()
        devs[k] = mat[:, k].std()

    norm_mat = np.ndarray(shape=(rows, cols), dtype=float)

    for i in range(rows):
        for j in range(cols):
            aux = mat[i, j] - means[j] / devs[j]
            norm_mat[i, j] = aux

    return norm_mat, means, devs
    
        

data1 = carga_csv("ex1data1.csv")
data2 = carga_csv("ex1data2.csv")

#gradient_desc(data1)
gradient_desc_multi_var(data2)