""" 
Gives the curves of paraxial electrons given a rotationally symmetric potential
constrained on the optical axis
"""

import numpy as np
from scipy import integrate
import matplotlib.pyplot as plt


def phi(z: float):
    """Potential along the optical axis

    Args:
        z (float): Distance along the optical axis

    Returns:
        float: electric potential at z
    """
    return 1.0 + 0.5 * np.sin(z)


def phi_prime(z: float):
    """z derivative of the potential on the axis

    Args:
        z (float): Distance along the optical axis

    Returns:
        float: Derivative of electric potential at z
    """
    return 0.5 * np.cos(z)


def rot_symm_field(z: float, position_slope_vector: list) -> list:
    """
    ODE to be fed into scipy.solve_ivp

    Args:
        z (float): Axial distance
        position_slope_vector (List with two floats):
            First element is transverse distance,
            Second element is the z derivative of the transverse distance

    Returns:
        list: List of derivatives of the input. That is,
            the first element is the first derivative of the transverse distance,
            and the second element is the second derivative of the transverse distance
    """
    return [
        position_slope_vector[1],
        -3.0 / 16.0 * (phi_prime(z) / phi(z)) ** 2 * position_slope_vector[0],
    ]


if __name__ == "__main__":
    # Calculate and plot the trajectories
    slopes = np.linspace(-0.2, 0.2, 10)
    z_vals = np.arange(0, 25.0, 0.001)
    tracks = []
    # Initial values (y0) should be computed with the potential,
    # because the initial values are of R = r*phi**.25, not r itself
    for slope in slopes:
        print(slope)
        solution = integrate.solve_ivp(
            rot_symm_field,
            t_span=[z_vals[0], z_vals[-1]],
            y0=[
                1.0,
                slope,
            ],
            t_eval=z_vals,
        )
        plt.plot(
            solution.t,
            solution.y[0, :] / phi(solution.t) ** 0.25,
        )

    plt.xlabel("axial coordinate")
    plt.ylabel("transverse coordinate")
    plt.title("Electron Trajectory in oscillating rotationally symmetric potential")
    plt.gca().set_aspect("equal")
    plt.show()
