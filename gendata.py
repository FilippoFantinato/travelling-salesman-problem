import argparse
import random
import math
from enum import Enum
from collections import defaultdict


class TSPInformation:
    def __init__(self, name, N):
        self.name = name
        self.comment = ''
        self.dimension = N
        self.type = "TSP"
        self.edge_weight_type = "EUC_2D"


def read_information(name: str, N: int) -> TSPInformation:
    info: TSPInformation = TSPInformation(name, N)

    tmp_name = input(f'NAME: ({name}) ').strip()
    if tmp_name:
        info.name = tmp_name

    info.comment = input('COMMENT: ').strip()

    return info


def get_number_holes(length: float, width: float):
    HOLE_DIM = 3; HOLE_DISTANCE = 1

    dim = HOLE_DIM + HOLE_DISTANCE

    n_holes_length = math.floor(length / dim)
    n_holes_width  = math.floor(width / dim)

    return n_holes_length, n_holes_width


def generate_tsp(
        N: int, 
        n_holes_length: float, 
        n_holes_width: float,
        length: float,
        width: float):
    grid = [(i, j) for i in range(n_holes_length) for j in range(n_holes_width)]

    data = []
    for (i, j) in random.sample(grid, N):
        data.append((i*length / n_holes_length, j*width / n_holes_width))

    return data


def write_file(out: str, name: str, info: TSPInformation, data):
    with open(f"{f'{out}/' if out else ''}{name}.tsp", "w") as fd:
        fd.write(f'NAME: {info.name}\n')
        
        if info.comment:
            fd.write(f'COMMENT: {info.comment}\n')

        fd.write(f'DIMENSION: {info.dimension}\n')
        fd.write(f'TYPE: {info.type}\n')
        fd.write(f'EDGE_WEIGHT_TYPE: {info.edge_weight_type}\n')
        fd.write('NODE_COORD_SECTION\n')
        for v, (x, y) in enumerate(data):
            fd.write(f'{v+1} {x} {y}\n')

        fd.write("EOF")


def init_args():
    parser = argparse.ArgumentParser()

    def check_positivity(v):
        v = int(v)
        if v < 0:
            raise argparse.ArgumentTypeError(f"{v} is an invalid positive int value")
        return v

    parser.add_argument(
        "--name", 
        type=str, 
        required=True, 
        help="Name of the file to generate"
    )
    parser.add_argument(
        "-N",
        type=int,
        required=True,
        help="Number of points",
    )
    parser.add_argument(
        "--out", 
        type=str,
        default="data",
        help="Output directory"
    )
    parser.add_argument(
        "--length",
        type=check_positivity,
        default=10,
        help=""
    )
    parser.add_argument(
        "--width",
        type=check_positivity,
        default=10,
        help=""
    )

    return parser


def main():
    args = init_args().parse_args()

    n_holes_length, n_holes_width = get_number_holes(args.length, args.width)

    if(args.N > (n_holes_length * n_holes_width)): 
        raise Exception(f"Not enough space for {args.N} holes.")

    info = read_information(args.name, args.N)
    data = generate_tsp(args.N, 
                        n_holes_length, 
                        n_holes_width, 
                        args.length, 
                        args.width)

    write_file(args.out, args.name, info, data)


if __name__ == "__main__":
    main()
