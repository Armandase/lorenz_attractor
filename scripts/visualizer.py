import argparse
import string
import matplotlib.pyplot as plt


def main(filename: string):
    x, y, z, t = [], [], [], []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split(';')
            if len(parts) == 4:
                x.append(float(parts[0]))
                y.append(float(parts[1]))
                z.append(float(parts[2]))
                t.append(float(parts[3]))

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(x, y, z)
    ax.set_xlabel('X axis')
    ax.set_ylabel('Y axis')
    ax.set_zlabel('Z axis')
    plt.title('Lorenz Attractor Visualization')
    plt.show()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Visualize Lorenz Attractor data from a log file.")
    parser.add_argument("filename", type=str, help="Path to the log file containing attractor data.")
    args = parser.parse_args()
    main(args.filename)