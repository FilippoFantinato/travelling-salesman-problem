import argparse

def init_args():
    parser = argparse.ArgumentParser()

    def check_positive(v):
        v = int(v)
        if v <= 0:
            raise argparse.ArgumentTypeError(f"{v} is an invalid positive int value")
        return v

    parser.add_argument(
        "--name", type=str, required=True, help="Name of the file to generate"
    )
    parser.add_argument(
        "-N",
        type=int,
        required=True,
        help="Number of points",
    )
    parser.add_argument(
        "--max",
        type=check_positive,
        required=True,
        help="How many dataset files to load"
    )
    parser.add_argument(
        "--min",
        type=check_positive,
        required=True,
        help="How many times to run an algorithm"
    )

    return parser

def main():
    args = init_args().parse_args()

    if args.min >= args.max:
        raise "Max must be greater than Min"

if __name__ == "__main__":
    main();
