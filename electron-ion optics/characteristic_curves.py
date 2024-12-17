import numpy as np
from scipy import integrate
import matplotlib.pyplot as plt


def phi(z):
    return 1.0 + 0.5 * np.sin(z)


def phi_prime(z):
    return 0.5 * np.cos(z)


def rot_symm_field(z, X):
    return [X[1], -3.0 / 16.0 * (phi_prime(z) / phi(z)) ** 2 * X[0]]


def integrand(t, Y):
    return [Y[1], -2 * Y[0] - Y[1]]


def main():
    slopes = np.arange(-0.1, 0.1, 10)
    times = np.arange(0, 25.0, 0.001)
    tracks = []
    # for slope in slopes:
    solution = integrate.solve_ivp(
        rot_symm_field,
        t_span=[times[0], times[-1]],
        y0=[
            1.0,
            0.0,
        ],  # Initial values should be computed with the potential, because the initial values are of R = r*phi**.25, not r itself
        t_eval=times,
    )
    plt.plot(
        solution.t,
        solution.y[0, :] / phi(solution.t) ** 0.25,
        label="y",
    )
    plt.plot(solution.t, phi(solution.t), label="potential at y=0")
    plt.plot(
        solution.t,
        phi(solution.t) + solution.y[0, :] ** 2 / 4 * np.sin(solution.t),
        label="potential at position",
    )
    plt.xlabel("axial coordinate")
    plt.ylabel("transverse coordinate")
    plt.title("Electron Trajectory in oscillating rotationally symmetric potential")
    plt.gca().set_aspect("equal")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
