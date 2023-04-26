import argparse
import random
from enum import Enum
from collections import defaultdict


class TSPType(Enum):
    tsp = "TSP"
    atsp = "ATSP"

    def __str__(self):
        return self.value


class EdgeWeightType(Enum):
    euc2d    = "EUC_2D"
    geo      = "GEO"
    explicit = "EXPLICIT"
    att      = "ATT"
    
    def __str__(self):
        return self.value


class EdgeWeightFormat(Enum):
    full_matrix = "FULL_MATRIX"

    def __str__(self):
        return self.value


class TSPInformation:
    def __init__(self, name, N, tsp_type, edge_weight_format):
        self.name = name
        self.comment = ''
        self.dimension = N
        self.type = tsp_type
        self.edge_weight_type = ''
        self.edge_weight_format = edge_weight_format


def read_information(name: str, N: int, tsp_type: TSPType) -> TSPInformation:
    info: TSPInformation = TSPInformation(name, N, tsp_type, EdgeWeightFormat.full_matrix)

    tmp_name = input(f'NAME: ({name}) ').strip()
    if tmp_name:
        info.name = tmp_name

    info.comment = input('COMMENT: ').strip()

    if tsp_type == TSPType.atsp:
        info.edge_weight_type = EdgeWeightType.explicit
    elif tsp_type == TSPType.tsp:
        info.edge_weight_type = EdgeWeightType(input("EDGE_WEIGHT_TYPE: ").strip().upper())

    return info


def generate_asymmetric_tsp(N: int, min: float, max: float):
    per_line = 10

    data = defaultdict(list)
    for n in range(N):
        i = n // per_line
        w = round(random.uniform(min, max), 2)
        data[i].append(w)
    return data


def generate_symmetric_tsp(N: int, min: float, max: float):
    if min >= max: raise "Max must be greater than Min"

    data = []
    for i in range(N):
        x = round(random.uniform(min, max), 2)
        y = round(random.uniform(min, max), 2)
        data.append((i+1, x, y))
    return data


def write_file(out: str, name: str, info: TSPInformation, data):
    with open(f"{f'{out}/' if out else ''}{name}.tsp", "w") as fd:
        fd.write(f'NAME: {info.name}\n')
        
        if info.comment:
            fd.write(f'COMMENT: {info.comment}\n')

        fd.write(f'DIMENSION: {info.dimension}\n')
        fd.write(f'TYPE: {info.type}\n')
        fd.write(f'EDGE_WEIGHT_TYPE: {info.edge_weight_type}\n')
        
        if info.edge_weight_type == EdgeWeightType.explicit:
            fd.write(f'EDGE_WEIGHT_FORMAT: {info.edge_weight_format}\n')

        if info.edge_weight_type == EdgeWeightType.explicit:
            fd.write('EDGE_WEIGHT_SECTION\n')
            for i in data:
                for w in data[i]:
                    fd.write(f' {w}')
                fd.write('\n')
        else:
            fd.write('NODE_COORD_SECTION\n')
            for (v, x, y) in data:
                fd.write(f'{v} {x} {y}\n')

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
        "--type", 
        type=TSPType,
        default=TSPType.tsp,
        help="TSP type"
    )
    parser.add_argument(
        "--out", 
        type=str,
        default="data",
        help="Output directory"
    )
    parser.add_argument(
        "--min",
        type=check_positivity,
        default=1,
        help="How many times to run an algorithm"
    )
    parser.add_argument(
        "--max",
        type=check_positivity,
        default=10,
        help="How many dataset files to load"
    )

    return parser


def main():
    args = init_args().parse_args()

    generators = {
        TSPType.tsp: generate_symmetric_tsp,
        TSPType.atsp: generate_asymmetric_tsp
    }

    info = read_information(args.name, args.N, args.type)
    
    data = generators[args.type](args.N, args.min, args.max)

    write_file(args.out, args.name, info, data)


if __name__ == "__main__":
    main()
