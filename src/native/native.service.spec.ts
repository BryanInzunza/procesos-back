import { Test, TestingModule } from '@nestjs/testing';
import { NativeService } from './native.service';

describe('NativeService', () => {
  let service: NativeService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [NativeService],
    }).compile();

    service = module.get<NativeService>(NativeService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });
});
