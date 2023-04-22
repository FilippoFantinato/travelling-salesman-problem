import argparse
import random
from enum import Enum


class TSPType(Enum):
    tsp     = "stsp"
    atsp    = "atsp"

    def __str__(self):
        return self.value


class EdgeWeightType(Enum):
    euc2d    = "EUC2D"
    geo      = "GEO"
    explicit = "EXPLICIT"
    att      = "ATT"
    
    def __str__(self):
        return self.value


class EdgeWeightFormat(Enum):
    full_matrix = "FULL_MATRIX"

    def __str__(self):
        return self.value


def read_information(name, type, N):
    info = {
        name: name,
        comment: "",
        dimension: N
        type: type,
        edge_weight_type: ''
        edge_weight_format: ''
    }
    info.name = input('NAME: ({name})')
    info.comment = input('COMMENT: ')
    
    if type == TSPType.atsp:
        info.edge_weight_type = EdgeWeightType.explicit
    elif type == TSPType.stsp:
        info.edge_weight_type = EdgeWeightType[input("EDGE_WEIGHT_TYPE: ").upper()]

    if info.edge_weight_type == EdgeWeightType.explicit:
        info.edge_weight_format = EdgeWeightFormat[input("EDGE_WEIGHT_FORMAT: ").upper()]

    return data


def generate_asymmetric_tsp(N):
    print("Insert all the weights")

    data = []
    for i in range(N):
        row = []
        for j in range(N):
            print("({i}, {j})")
            w = float(input("({i}, {j})>"))
            row.append(w)
        data.append(row)
    return data


def generate_symmetric_tsp(N, min, max):
    if min >= max: raise "Max must be greater than Min"

    data = []
    for i in range(N):
        row = []
        for j in range(N):
            v = (i*N+j) + 1
            x = round(random.uniform(min, max), 2)
            y = round(random.uniform(min, max), 2)
            row.append((v, x, y))
        data.append(row)
    return data


def write_file(name, info, data):
    with open("{name}.tsp", "w") as fd:
        fd.writelines()


def init_args():
    parser = argparse.ArgumentParser()

    def check_positive(v):
        v = int(v)
        if v <= 0:
            raise argparse.ArgumentTypeError(f"{v} is an invalid positive int value")
        return v

    parser.add_argument(
        "--name", 
        type=str, 
        required=True, 
        help="Name of the file to generate"
    )
    parser.add_argument(
        "--type", 
        type=TSPType,
        default=TSPType.tsp
        help="TSP type"
    )
    parser.add_argument(
        "-N",
        type=int,
        required=True,
        help="Number of points",
    )
    parser.add_argument(
        "--min",
        type=check_positive,
        default=1
        help="How many times to run an algorithm"
    )
    parser.add_argument(
        "--max",
        type=check_positive,
        default=10
        help="How many dataset files to load"
    )

    return parser


def main():
    args = init_args().parse_args()

    generators = {
        TSPType.stsp: generate_symmetric_tsp,
        TSPType.atsp: generate_asymmetric_tsp
    }

    info = read_information(args.name, args.type, args.N)
    data = generators[args.type](args.N, args.min, args.max)

    write_file(name, info, data)

if __name__ == "__main__":
    main()
