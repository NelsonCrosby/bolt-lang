

class State:
    def __init__(self, matches, ids, terminating=False):
        self.matches = matches
        self.ids = ids if isinstance(ids, list) else [ids]
        self.terminating = terminating
        self.paths = []

    def add_path(self, path):
        self.paths.append(path)
    
    def can_merge_with(self, other):
        if self.terminating or other.terminating:
            return False

        if len(self.matches) == len(other.matches):
            for i, match in enumerate(self.matches):
                if match != other.matches[i]:
                    return False
            return True

        return False

    def merge(self, other):
        if not self.can_merge_with(other):
            return None

        new = State(self.matches, self.ids + other.ids)

        i_have_self = False
        for path in self.paths:
            if path is self:
                i_have_self = True
            else:
                new.add_path(path)

        other_has_self = False
        for path in other.paths:
            if path is other:
                other_has_self = True
            else:
                new.add_path(path)

        if i_have_self and other_has_self:
            new.add_path(new)
        elif i_have_self:
            new.add_path(self)
        elif other_has_self:
            new.add_path(other)

        return new



class StateMatch:
    def __init__(self, c, d=None):
        self.c = c
        self.d = d
    
    def __eq__(self, other):
        return self.c == other.c and self.d == other.d


def compile(src):
    pass
